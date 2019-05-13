#include"lodepng.h"
#include <boost/filesystem.hpp>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;
using namespace boost::filesystem;

bool compress(path& image, int threshold);