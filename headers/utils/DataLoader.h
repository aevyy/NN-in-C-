#pragma once


#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

namespace utils {
    class DataLoader {  
    public:
        // Loads a CSV file
        static std::vector< std::vector<double> > fetchData(const std::string& pathToFile);
    };
}