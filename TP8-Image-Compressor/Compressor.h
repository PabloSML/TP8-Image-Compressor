#include"lodepng.h"
#include <boost/filesystem.hpp>
#include <list>
#include <fstream>
using namespace boost::filesystem;
bool compressor(path& image, list<path> compressed_list, const int threshold);