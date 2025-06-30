#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>


using namespace std;

vector<pair<string, vector<string>>> read_csv(string filename){
    // initializes a vector of pairs of strings and int vectors {string: column headers, 
    // vectors: column data}

    vector<pair<string, vector<string>>> result;

    ifstream myFile(filename);

    if(!myFile.is_open()) throw runtime_error("Could not open file");

    string line, colname;
    string val;

    if (myFile.good()){
        getline(myFile, line);
        stringstream ss(line);
        while(getline(ss, colname, ',')){
            result.push_back({colname, vector<string>{}});
        }
    }

    while(getline(myFile, line)){
        stringstream ss(line);

        int colIdx = 0;

        while (getline(ss, val, ',')) {
            if (colIdx < result.size())
                result.at(colIdx).second.push_back(val);
            ++colIdx;
        }

    }

    myFile.close();
    return result;

};

int main(){
    // gets all the column headers and data
    vector<pair<string, vector<string>>> data = read_csv("../data/AAPL.csv");

    // unpacks the pair
    auto[close, close_vals] = data[1];

    // looks at only close values
    for (auto j = 0; j < 10; ++j){
        cout << close_vals[j] << "\n";
    }
};