#include"lodepng.h"
#include <boost/filesystem.hpp>
#include <list>
#include <fstream>

bool compressor(boost::filesystem::path& image, list<boost::filesystem::path> compressed_list, const int threshold);