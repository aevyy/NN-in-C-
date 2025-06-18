#include "../../headers/utils/DataLoader.h"

std::vector< utils::Sample > utils::DataLoader::fetchData(
    const std::string& path,
    int inputSize,
    int targetSize ) {

    std::vector<utils::Sample> dataset;
    std::ifstream infile(path);

    if (!infile.is_open()) {
        std::cerr << "!!! Failed to Open File !!!"
        << std::endl << " --> " << path
        << std::endl;
        return dataset;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::vector<double> input, target;
        std::stringstream ss(line);
        std::string token;

        // Splitting the line by commas
        while (std::getline(ss, token, ',')) {
            try {
                double val = std::stod(token);
                if (input.size() < inputSize) {
                    input.push_back(val);
                } else {
                    target.push_back(val);
                }
            } catch (const ::std::invalid_argument&) {
                std::cerr << "!!! Invalid Number !!!"
                << std::endl << token << " (Skipped)"
                << std::endl;
            }
        }

        if (input.size() == inputSize && target.size() == targetSize) {
            // Normalizing input and target values
            // const double inputScale = 10.0;
            // const double targetScale = 10.0;

            // for (double& x : input) x /= inputScale;
            // for (double& x : target) x /= targetScale;

            dataset.push_back({input, target});
            
        } else {
            std::cerr << "Skipped malformed row (expected "
            << inputSize + targetSize << " values, got "
            << input.size() + target.size() << ")\n";
        }
    }

    return dataset;
}