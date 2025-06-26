#pragma once


#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>

using namespace std;

namespace utils
{
  class Misc
  {
  public:
    static vector< vector<double> > fetchData(string path);
  };
}