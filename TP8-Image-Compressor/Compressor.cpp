#include "Compressor.h"

using namespace std;

int compress(unsigned char* out, unsigned int w, unsigned int h, const int threshold, boost::filesystem::ofstream& output_file, unsigned int wmin = 0, unsigned int hmin = 0);

bool compressor(path& image,  list<path> compressed_list, const int threshold)
{
	unsigned int w, h;
	unsigned char* out;

	int error = lodepng_decode32_file(&out, &w, &h, image.filename().string().c_str());

	if (error)
	{
		return false;
	}
	else
	{
		path out_file;
		boost::filesystem::ofstream output{ out_file };
		compress(out, w, h, threshold, output);
		compressed_list.push_back(out_file);
		return true;
	}
}

int compress(unsigned char* out, unsigned int w, unsigned int h, const int threshold, boost::filesystem::ofstream& output_file, unsigned int wmin=0, unsigned int hmin=0)
{
	
	char r=0, g=0, b=0, rprom=0, gprom=0, bprom=0, rmax=0, rmin=0, gmax=0, gmin=0, bmax=0, bmin=0;
	int pixel_count = 0;
	for (int i = wmin; i < w; i++)
	{
		for (int j = hmin; j < h; j++)
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
	rprom = rprom / pixel_count;
	gprom = gprom / pixel_count;
	bprom = bprom / pixel_count;

	int weight= (rmax - rmin) + (gmax - gmin) + (bmax - bmin);
	if (weight > threshold)
	{
		output_file << "D";

		compress(out, (w / 2), (h / 2), threshold, output_file, wmin, hmin);	//primer cuadrante

		compress(out, (w), (h/2), threshold, output_file, w/2, hmin);			//segundo cuadrante

		compress(out, (w / 2), (h), threshold, output_file, wmin, (h/2));		//tercer cuadrante

		compress(out, (w), (h), threshold, output_file, (w / 2), (h/2));		//cuarto cuadrante

		return 1;
	}
	else
	{
		output_file << "N";
		output_file << rprom << gprom << bprom;
		return 1;
	}
}