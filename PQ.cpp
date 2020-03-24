#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <queue>
#include <cassert>

//#define FILEPATH "C:\\Users\\Student241165\\source\\repos\\RPQ\\Text.txt"
#define FILEPATH "C:\\Users\\Student241165\\Desktop\\RPQ\\data10.txt"

struct comparatorReversedR
{
    // queue elements are vectors so we need to compare those
    bool operator()(std::vector<int> const& a, std::vector<int> const& b) const
    {
        // sanity checks
        assert(a.size() == 4);
        assert(b.size() == 4);

        // reverse sort puts the lowest value at the top    
        return a[0] > b[0];
    }
};
using my_priority_queue = std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, comparatorReversedR>;

class RPQ {
public:
    RPQ() {
        loadFile();
    }
private:
    my_priority_queue MPQOfProcesses;
    std::vector<int> Process;
    int numberOfProcess = 0;
    int numberOfParameters = 0;
    int buffer;
    std::vector<int> wykonaneProcesy;
public:
    void loadFile();
    void PrintProcesses();
    void CMAX();
    void SortByR();
    void SortByQR();
    void SortCarlier();
    void SortSchrange();
    void Order();
    void SortSchrangePMTN();
};

int main() {
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
            Process.push_back(j + 1);
            MPQOfProcesses.push(Process);
        }
    }
    else {
        std::cout << "Nie ma takiego pliku";
    }
    inputFile.close();
}
