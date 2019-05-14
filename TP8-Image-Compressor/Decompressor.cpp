#include "Decompressor.h"
#define NRGB_SIZE 4
#define ALPHA 128

static bool decompressor(string::iterator& itr, unsigned char* destImg, unsigned int w, unsigned int h, unsigned int wmin, unsigned int hmin, unsigned int side);

bool decompress(path& compressedImg)
{
	bool success = false;
	std::ifstream is(compressedImg.string().c_str(), std::ifstream::binary);
	if (is)
	{
		string temp = compressedImg.stem().string() + ".png";	// se genera el nombre del archivo descomprimido
		const char* newName = temp.c_str();
		string bufferStr("");
		int beg, end;
		unsigned int side;
								// se obtiene un string con el contenido del archivo comprimido
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);
		char * buffer = new char[length];
		is.read(buffer, length);
		is.close();
		for (int i = 0; i < length; i++)
			bufferStr.push_back(buffer[i]);
								// se obtiene la longitud del lado de la imagen (debe ser cuadrada entonces side = w = h)
		beg = 0;
		end = bufferStr.find_first_of("DN");
		string sideStr = bufferStr.substr(beg, end - beg);
		side = stoi(sideStr);
		beg = end;

		string toDecompress = bufferStr.substr(beg);
		string::iterator itr = toDecompress.begin();

		unsigned char* image = new unsigned char[side*side*NRGB_SIZE];

		decompressor(itr, image, side, side, 0, 0, side);

		lodepng_encode32_file(newName, image, side, side);

		delete[] buffer;
		delete[] image;
		success = true;
	}
	return success;
}

static bool decompressor(string::iterator& itr, unsigned char* destImg, unsigned int w, unsigned int h, unsigned int wmin, unsigned int hmin, unsigned int side)
{
	if (*itr == 'N') // caso base
	{
		itr++;
		unsigned char red = *itr;
		itr++;
		unsigned char green = *itr;
		itr++;
		unsigned char blue = *itr;
		itr++;
		for (unsigned int i = hmin; i < h; i++)
		{
			for (unsigned int j = wmin*NRGB_SIZE; j < w*NRGB_SIZE; j += NRGB_SIZE)
			{
				destImg[(i*side*NRGB_SIZE) + j] = red;		
				destImg[(i*side*NRGB_SIZE) + j + 1] = green;
				destImg[(i*side*NRGB_SIZE) + j + 2] = blue;
				destImg[(i*side*NRGB_SIZE) + j + 3] = ALPHA;	// Arbitrary Alpha (128)
			}
		}
	}
	else
	{
		itr++;
		unsigned int halfW = wmin + ( (w - wmin) / 2);
		unsigned int halfH = hmin + ((h - hmin) / 2);

		decompressor(itr, destImg, halfW, halfH, wmin, hmin, side);	// primer cuadrante
		decompressor(itr, destImg, w, halfH, halfW, hmin, side);		// segundo cuadrante
		decompressor(itr, destImg, halfW, h, wmin, halfH, side);		// tercer cuadrante
		decompressor(itr, destImg, w, h, halfW, halfH, side);			// cuarto cuadrante
	}

	return true;
}