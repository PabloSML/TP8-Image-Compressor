#pragma once
#include <list>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;

list<path>* lookForPNGs(path& dir);