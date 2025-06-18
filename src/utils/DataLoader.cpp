#include "../../headers/utils/DataLoader.h"

std::vector< std::vector<double> > utils::DataLoader::fetchData(const std::string& pathToFile) {
    std::vector<std::vector<double>> data;

    std::ifstream infile(pathToFile);
    if (!infile.is_open()) {
        std::cerr << "!!! Failed to Open File !!!"
        << std::endl << " --> " << pathToFile
        << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string token;

        // Splitting the line by commas
        while (std::getline(ss, token, ',')) {
            try {
                row.push_back(std::stod(token)); // string -> double
            } catch (const ::std::invalid_argument& e) {
                std::cerr << "!!! Invalid Number !!!"
                << std::endl << token << " (Skipped)"
                << std::endl;
            }
        }

        if (!row.empty()) {
            data.push_back(row);
        }
    }

    infile.close();
    return data;
}