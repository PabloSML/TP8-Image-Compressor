#include "Decompressor.h"
#define PIXEL_SIZE 4
#define ALPHA 0
/*
Ejemplo para pensar
1200DDNRGBNRGBNRGBNRGBNRGBDNRGBDNRGBNRGBNRGBNRGBDNRGBNRGBNRGBNRGBNRGBNRGBNRGBNRGBNRGBNRGBNRGBDNRGBNRGBNRGBNRGB
*/

bool decompress(path& compressedImg)
{
	bool success = false;
	std::ifstream is(compressedImg.string().c_str(), std::ifstream::binary);
	if (is)
	{
		string temp = compressedImg.stem().string() + ".png";	// se genera el nombre del archivo descomprimido
		const char* newName = temp.c_str();
		string bufferStr("");
		//string image("");
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

		unsigned char* image = new unsigned char[side*side*PIXEL_SIZE];

		decompressor(toDecompress, image, side, side, 0, 0);

		//lodepng_encode32_file(newName, , side, side);

		delete[] buffer;
		delete[] image;
		success = true;
	}
	return success;
}

bool decompressor(string& toDecompress, unsigned char* destImg, unsigned int w, unsigned int h, unsigned int wmin, unsigned int hmin)
{
	if (toDecompress[0] == 'N')
	{
		for (unsigned int i = wmin; i <= w; i++)
		{
			for (unsigned int j = hmin; j <= h; j++)
			{
				destImg[(i*w) + j] = toDecompress[1];		// Red
				destImg[(i*w) + j + 1] = toDecompress[2];	// Green
				destImg[(i*w) + j + 2] = toDecompress[3];	// Blue
				destImg[(i*w) + j + 3] = ALPHA;				// Arbitrary Alpha (0)
			}
		}
	}
	else
	{
		
	}
}

/*
		D | N R G B | N R G B | N R G B | N R G B

		D | D | N R G B | N R G B | N R G B | N R G B | N R G B | N R G B | N R G B


*/