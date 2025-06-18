#pragma once


#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

namespace utils {

    using Sample = std::pair<std::vector<double>, std::vector<double>>;

    class DataLoader {
    public:
        // Loads a CSV file
        static std::vector< Sample > fetchData(
                const std::string& path,
                int inputSize,
                int targetSize );
    };
}