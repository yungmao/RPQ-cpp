#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>

#define FILEPATH "C:\\Users\\Student241165\\Desktop\\RPQ\\data100.txt"

class RPQ {
public:
    RPQ() {
        loadFile();
        SortByR();
        CMAX();
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
    void SortByR();
    void SortByPermutation();
    void CMAX();
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
    std::cout << "Wartosci Procesow: " << std::endl;
    for (auto i : VectorOfProcesses) {
        for (auto j : i) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
}
void RPQ::SortByR() {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::sort(VectorOfProcesses.begin(), VectorOfProcesses.end());
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Czas Wykonania funkcji sort R: " << duration <<"ms"<<std::endl;
}
void RPQ::SortByPermutation() {}
void RPQ::CMAX() {
    int endtime = 0;
    int cmax = 0;
    int starttime = 0;
    std::vector<int> foo;
    foo = VectorOfProcesses[0];
    starttime = foo[0] + foo[1];
    for (int i = 1; i < numberOfProcess; i++) {
        starttime = cmax;
        foo = VectorOfProcesses[i];
        if (foo[0] <= starttime) {
            cmax = starttime + foo[1];
            if (endtime < (cmax+foo[2])) {
                endtime = cmax + foo[2];
            }
        }
        else
        {
            starttime = starttime + (foo[0] - starttime);
            cmax = starttime + foo[1];
            if (endtime < (cmax + foo[2])) {
                endtime = cmax + foo[2];
            }
        }
    }

    std::cout << "Wynik CMAX = " << endtime << std::endl;
}