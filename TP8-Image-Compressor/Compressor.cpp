#include "Compressor.h"



int compressor(unsigned char* out, unsigned int w, unsigned int h, const int threshold, boost::filesystem::ofstream& output_file, unsigned int wmin = 0, unsigned int hmin = 0);

bool compress(path& image, const int threshold, list<path>& compressed_list, const char* compressedExtension)
{
	unsigned int w, h;
	unsigned char* out;
	bool ret = false;

	int error = lodepng_decode32_file(&out, &w, &h, image.string().c_str());		//decode de la imagen

	if (w % 2)			//si la altura o el ancho no son pares, le resta un pixel (consideré que sacarle una linea de pixeles no se notaria enla imagen)
	{
		w--;
	}
	if (h % 2)
	{
		h--;
	}

	if (!error)
	{
		path out_file (image.stem().string()+ compressedExtension ); //creoel path con nombre "imagen.compressedExtension"
		cout << "Created path " << out_file << endl;
		boost::filesystem::ofstream output{ out_file };		//pongo out_file como output
		compressor(out, w, h, threshold, output);				//funcion que comprime
		compressed_list.push_back(out_file);			//agrego el path a la lista
		ret = true;
	}
	else
	{
		cout << "Error al hacer el decode de la imagen" << endl;
	}
	return ret;
}

int compressor(unsigned char* out, unsigned int w, unsigned int h, const int threshold, boost::filesystem::ofstream& output_file, unsigned int wmin, unsigned int hmin)
{
	
	char r=0, g=0, b=0, rprom=0, gprom=0, bprom=0, rmax=0, rmin=0, gmax=0, gmin=0, bmax=0, bmin=0;
	int pixel_count = 0;
	for (unsigned int i = wmin; i < w; i++)
	{			//recorro pixel a pixel el cuadrante
		for (unsigned int j = hmin; j < h; j++)
		{
			//tomo valoresRGB
			r=out[(i*w) + j];
			g=out[(i*w) + j + 1];
			b=out[(i*w) + j + 2];

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
			if (g > gmin)
			{
				gmin = g;
			}
			if (b > bmin)
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
	if (pixel_count == 0)
	{
		pixel_count = 1;
	}
	rprom = rprom / pixel_count;
	gprom = gprom / pixel_count;
	bprom = bprom / pixel_count;

	int weight= (rmax - rmin) + (gmax - gmin) + (bmax - bmin);
	if (weight > threshold)
	{
		output_file.put('D');
		cout << "D" << endl;
		compressor(out, (w / 2), (h / 2), threshold, output_file, wmin, hmin);	//primer cuadrante

		compressor(out, (w), (h/2), threshold, output_file, w/2, hmin);			//segundo cuadrante

		compressor(out, (w / 2), (h), threshold, output_file, wmin, (h/2));		//tercer cuadrante

		compressor(out, (w), (h), threshold, output_file, (w / 2), (h/2));		//cuarto cuadrante

		return 1;
	}
	else
	{
		output_file.put('N');
		output_file << rprom << gprom << bprom;
		cout << "N" << rprom << gprom << bprom << endl;
		return 1;
	}
}
