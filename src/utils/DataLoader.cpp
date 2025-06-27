#include "../../headers/utils/DataLoader.h"
#include <stdexcept>

vector< vector<double> > utils::Misc::fetchData(string path) {
  vector< vector<double> > data;

  ifstream infile(path);
  
  if (!infile.is_open()) {
    cerr << "Error: Could not open file " << path << endl;
    return data;
  }

  string line;
  int lineNumber = 0;
  while(getline(infile, line)) {
    lineNumber++;
    
    // Skip empty lines
    if (line.empty()) {
      continue;
    }
    
    vector<double>  dRow;
    string          tok;
    stringstream    ss(line);

    while(getline(ss, tok, ',')) {
      // Trim whitespace
      tok.erase(0, tok.find_first_not_of(" \t\r\n"));
      tok.erase(tok.find_last_not_of(" \t\r\n") + 1);
      
      // Skip empty tokens
      if (tok.empty()) {
        continue;
      }
      
      try {
        dRow.push_back(stof(tok));
      } catch (const std::invalid_argument& e) {
        cerr << "Error parsing line " << lineNumber << ", token: '" << tok << "'" << endl;
        throw;
      }
    }

    if (!dRow.empty()) {
      data.push_back(dRow);
    }
  }

  infile.close();
  return data;
}