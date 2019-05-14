#include "Compressor.h"

static int compressor(unsigned char* out, unsigned int w, unsigned int h, int threshold, string& output_string, unsigned int wmin, unsigned int hmin, unsigned int side);

bool compress(path& image, int threshold)
{
	unsigned int w, h;
	unsigned char* out;
	bool ret = false;

	int error = lodepng_decode32_file(&out, &w, &h, image.string().c_str());		//decode de la imagen
	
	if (w != h)			//chequeo imagen cuadrada
	{
		std::cout << "Imagen no es cuadrada" << std::endl;
		error= true;
	}
	double test = log2(w);
	if ((int)test != test)			//chequeo lados
	{
		cout << "Lados de la imagen deben ser potencia de 2" << endl;
		error = true;
	}

	threshold = ((255 * 3)*threshold) / 100; // la validez del threshold fue verificada de antemano al ser ingresada por el usuario

	if (!error)
	{
		path out_file (image.replace_extension(".eda"));	 //creo el path con nombre "imagen.eda"
		cout << "Created path to " << out_file.filename() << endl;
		boost::filesystem::ofstream os(out_file, boost::filesystem::ofstream::binary);
		if (os)
		{
			string output_string = to_string(w);
			compressor(out, w, h, threshold, output_string, 0, 0, w);	//funcion que comprime
			os.write(output_string.c_str(), output_string.length());
		}
	}
	else
	{
		cout << "Error en la compresion de la imagen" << endl;
	}
	free(out);
	return ret;
}

static int compressor(unsigned char* out, unsigned int w, unsigned int h, int threshold, string& output_string, unsigned int wmin, unsigned int hmin, unsigned int side)
{
	unsigned char r=0, g=0, b=0, rmax=0, rmin=255, gmax=0, gmin=255, bmax=0, bmin=255;
	int pixel_count = 0, rprom = 0, gprom = 0, bprom = 0;
	for (unsigned int i = hmin; i < h; i++)
	{			//recorro pixel a pixel el cuadrante
		for (unsigned int j = wmin*4; j < w*4; j += 4)
		{
			//tomo valoresRGB
			r=out[(i*side*4) + j];
			g=out[(i*side*4) + j + 1];
			b=out[(i*side*4) + j + 2];

			//CHEQUEO MAXIMOS
			if (r > rmax)
			{
				rmax = r;
			}
			if (g > gmax)
			{
				gmax = g;
			}
			if (b > bmax)
			{
				bmax = b;
			}

			//CHEQUEO MINIMOS
			if (r < rmin)
			{
				rmin = r;
			}
			if (g < gmin)
			{
				gmin = g;
			}
			if (b < bmin)
			{
				bmin = b;
			}

			//sumo para promedio
			rprom += r;
			gprom += g;
			bprom += b;
			pixel_count++;
		}
	}

	//PROMEDIO RGB
	rprom = rprom / pixel_count;
	gprom = gprom / pixel_count;
	bprom = bprom / pixel_count;


	cout << "MAX " << "R "<<to_string(rmax) <<" G "<< to_string(gmax) <<" B "<< to_string(bmax) << endl;
	cout<< "MIN " <<"R " <<to_string(rmin) <<" G "<< to_string(gmin) <<" B "<< to_string(bmin) << endl;
	int weight= (rmax - rmin) + (gmax - gmin) + (bmax - bmin);
	
	if (weight > threshold)
	{
		output_string.push_back('D');
		
		int new_w = wmin + ((w - wmin) / 2);
		int new_h = hmin + ((h - hmin) / 2);

		compressor(out, new_w, new_h, threshold, output_string, wmin, hmin, side);	//primer cuadrante
		compressor(out, (w), new_h, threshold, output_string, new_w, hmin, side);			//segundo cuadrante
		compressor(out, new_w, (h), threshold, output_string, wmin, new_h, side);		//tercer cuadrante
		compressor(out, (w), (h), threshold, output_string, new_w, new_h, side);		//cuarto cuadrante

		return 0;
	}
	else
	{
		output_string.push_back('N');
		output_string.push_back((unsigned char)rprom);
		output_string.push_back((unsigned char)gprom);
		output_string.push_back((unsigned char)bprom);

		return 0;
	}
}
