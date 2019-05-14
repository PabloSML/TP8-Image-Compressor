#include "Compressor.h"



int compressor(unsigned char* out, unsigned int w, unsigned int h, int threshold, boost::filesystem::ofstream& output_file, unsigned int wmin = 0, unsigned int hmin = 0);

bool compress(path& image, int threshold)
{
	unsigned int w, h;
	unsigned char* out;
	bool ret = false;

	int error = lodepng_decode32_file(&out, &w, &h, image.string().c_str());		//decode de la imagen
	
	if (w != h)			//chequeo imagen cuadrada
	{
		cout << "Imagen no es cuadrada" << endl;
		error= true;
	}
	double test = log2(w);
	if ((int)test != test)			//chequeo lados
	{
		cout << "Lados de la imagen deben ser potencia de 2" << endl;
		error = true;
	}

	if (threshold >= 0 || threshold <= 100)
	{
		threshold = ((255 * 3)*threshold) / 100;
	}
	else
	{
		cout << "Threshold must be 0-100 (percent)." << endl;
		error = true;
	}

	if (!error)
	{
		path out_file (image.replace_extension(".eda"));	 //creo el path con nombre "imagen.eda"
		cout << "Created path to " << out_file.filename() << endl;
		boost::filesystem::ofstream output{ out_file };		//pongo out_file como output
		output << w;
		if (!output.is_open())
		{
			cout << "No se pudo abrir output file" << endl;
		}
		else
		{
			compressor(out, w, h, threshold, output);				//funcion que comprime
			ret = true;
		}
	}
	else
	{
		cout << "Error en la compresion de la imagen" << endl;
	}
	free(out);
	return ret;
}

int compressor(unsigned char* out, unsigned int w, unsigned int h, int threshold, boost::filesystem::ofstream& output_file, unsigned int wmin, unsigned int hmin)
{
	unsigned char r=0, g=0, b=0, rmax=0, rmin=255, gmax=0, gmin=255, bmax=0, bmin=255;
	int pixel_count = 0, rprom = 0, gprom = 0, bprom = 0;
	for (unsigned int i = wmin; i < w; i++)
	{			//recorro pixel a pixel el cuadrante
		for (unsigned int j = hmin; j < h; j++)
		{
			//tomo valoresRGB
			r=out[+(i*w) + j];
			g=out[+(i*w) + j + 1];
			b=out[+(i*w) + j + 2];

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

	//cout << out[3]<< out[4] << out[5] << endl;
	//PROMEDIO RGB
	//cout << "rprom " << to_string(rprom) << "\t grom " << to_string(gprom) << "\t brom " << to_string(bprom) << endl;
	//cout << pixel_count << endl;
	rprom = rprom / pixel_count;
	gprom = gprom / pixel_count;
	bprom = bprom / pixel_count;

	//cout << "MAX " << "R "<<to_string(rmax) <<" G "<< to_string(gmax) <<" B "<< to_string(bmax) << endl;
	//cout<< "MIN " <<"R " <<to_string(rmin) <<" G "<< to_string(gmin) <<" B "<< to_string(bmin) << endl;
	int weight= (rmax - rmin) + (gmax - gmin) + (bmax - bmin);
	
	//cout <<"thres "<< to_string(threshold) <<" / "<<"weight"<< to_string(weight) << endl;
	if (weight > threshold)
	{
		output_file.put('D');
		
		
		int new_w = (w+wmin) / 2;
		int new_h = (h+hmin) / 2;
		
		
		

		compressor(out, new_w, new_h, threshold, output_file, wmin, hmin);	//primer cuadrante
		
		compressor(out, (w), new_h, threshold, output_file, new_w, hmin);			//segundo cuadrante
		
		compressor(out, new_w, (h), threshold, output_file, wmin, new_h);		//tercer cuadrante
		
		compressor(out, (w), (h), threshold, output_file, new_w, new_h);		//cuarto cuadrante
		
		return 1;
	}
	else
	{
		output_file.put('N');
		output_file << (char)rprom << (char)gprom << (char)bprom;
		//cout << "N" << endl;
		//cout << "rprom " << (char)rprom << "\t grom " << (char)gprom << "\t brom " << (char)bprom << endl;
		return 1;
	}
}
