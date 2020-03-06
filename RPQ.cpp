#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define FILEPATH "C:\\Users\\Student241165\\Desktop\\RPQ\\data10.txt"

class RPQ {
public:
    RPQ() {
        loadFile();
    }
private:
    std::vector<std::vector<int>> VectorOfProcesses;
    std::vector<int> Process;
    int numberOfProcess = 0;
    int numberOfParameters = 0;
    int buffer;

public:
    void loadFile();
    void PrintProcesses();

};

int main() {
    RPQ rpq;
    rpq.PrintProcesses();
    return 0;
}

void RPQ::loadFile() {
    std::ifstream inputFile;
    inputFile.open(FILEPATH);
    if (inputFile.is_open()) {
        inputFile >> numberOfProcess;
        inputFile >> numberOfParameters;
        for (int j = 0; j < numberOfProcess; j++) {
            Process.clear();
            for (int i = 0; i < numberOfParameters; i++) {
                inputFile >> buffer;
                Process.push_back(buffer);
            }
            VectorOfProcesses.push_back(Process);
        }
    }
    else {
        std::cout << "Nie ma takiego pliku";
    }
    inputFile.close();
}
void RPQ::PrintProcesses() {
    for (auto i : VectorOfProcesses) {
        for (auto j : i) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
}
