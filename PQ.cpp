#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <queue>
#include <cassert>

#define FILEPATH "C:\\Users\\Student241165\\source\\repos\\RPQ\\Text.txt"
//#define FILEPATH "C:\\Users\\Student241165\\Desktop\\RPQ\\data10.txt"

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
struct comparatorQ
{
    // queue elements are vectors so we need to compare those
    bool operator()(std::vector<int> const& a, std::vector<int> const& b) const
    {
        // sanity checks
        assert(a.size() == 4);
        assert(b.size() == 4);

        // reverse sort puts the lowest value at the top    
        return a[2] < b[2];
    }
};
using my_priority_queue = std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, comparatorReversedR>;
using finished_queue = std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, comparatorQ>;
class PQ {
public:
    PQ() {

        loadFile();
        /*
        PrintProcesses(MPQOfProcesses);
        Order(MPQOfProcesses);
        CMAX(MPQOfProcesses);
        */
        SortSchrange(MPQOfProcesses);
        CMAX();
        PrintProcesses();
        Order();

        SortSchrangePMTN(MPQOfProcesses);
        CMAX();
        PrintProcesses();
        Order();
    }
private:
    my_priority_queue MPQOfProcesses;
    std::vector<int> Process;
    int numberOfProcess = 0;
    int numberOfParameters = 0;
    int buffer;
    std::vector<std::vector<int>> ProcessInOrder;
public:
    void loadFile();
    void PrintProcesses(my_priority_queue q);
    void CMAX(my_priority_queue q);
    void Order(my_priority_queue q);
    void SortSchrange(my_priority_queue q);
    void SortSchrangePMTN(my_priority_queue q);
    void PrintProcesses();
    void CMAX();
    void Order();
};

int main() {
    PQ pq;
    return 0;
}
void PQ::loadFile() {
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
void PQ::PrintProcesses(my_priority_queue q) {
    while (!q.empty()) {
        std::vector<int> tmp;
        tmp = q.top();
        for (auto j : tmp) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
        q.pop();
    }
}
void PQ::Order(my_priority_queue q)
{
    while (!q.empty()) {
        std::vector<int> tmp;
        tmp = q.top();
        std::cout << tmp[3] << " ";
        q.pop();
    }
    std::cout << std::endl;
}
void PQ::CMAX(my_priority_queue q) {
    int endtime = 0;
    int cmax = 0;
    int starttime = 0;
    while (!q.empty()) {
        std::vector<int> foo;
        foo = q.top();
        starttime = foo[0] + foo[1];
        starttime = cmax;
        if (foo[0] <= starttime) {
            cmax = starttime + foo[1];
            if (endtime < (cmax + foo[2])) {
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
        q.pop();
    }
    std::cout << "Wynik CMAX = " << endtime << std::endl;
}
void PQ::SortSchrange(my_priority_queue q)
{
    finished_queue fq;
    std::vector<std::vector<int>> VFinal;
    std::vector<int> foo;
    auto t1 = std::chrono::high_resolution_clock::now();
    while (!q.empty()) {
        foo = q.top();
        int time = foo[0];
        do {
            do {
                if (q.size() != 0) {
                    foo = q.top();
                    if (foo[0] <= time) {
                        fq.push(foo);
                        q.pop();
                    }
                }
                if ((fq.size() == 0)) {
                    time = foo[0];
                }
            } while (!q.empty() && (foo[0] <= time));
            foo = fq.top();
            time += foo[1];
            ProcessInOrder.push_back(foo);
            fq.pop();
        } while (!q.empty() || (fq.size() != 0));
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Czas Wykonanie Algorytmu Schrange " << duration << "ms" << std::endl;
    }
}
void PQ::SortSchrangePMTN(my_priority_queue q)
{
    ProcessInOrder.clear();
    finished_queue fq;
    std::vector<int> NFinished;
    std::vector<int> foo;
    std::vector<int> exec;
    int kolejnosc = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    while (!q.empty()) {
        foo = q.top();
        int time = foo[0];
        do {
            do {
                if (q.size() != 0) {
                    foo = q.top();
                    if (foo[0] <= time) {
                        fq.push(foo);
                        q.pop();
                        if (kolejnosc != 0) {
                            if (foo[2] > exec[2]) {
                                NFinished = exec;
                                exec[1] = time - foo[0];
                                NFinished[1] -= exec[1];
                                time = foo[0];
                                ProcessInOrder.pop_back();
                                ProcessInOrder.push_back(NFinished);
                                if (exec[1] > 0) {
                                    fq.push(exec);
                                }
                            }
                        }
                    }
                }
                if ((fq.size() == 0)) {
                    time = foo[0];
                }
            } while (!q.empty() && (foo[0] <= time));
            foo = fq.top();
            time += foo[1];
            exec = foo;
            ++kolejnosc;
            ProcessInOrder.push_back(foo);
            fq.pop();
        } while (!q.empty() || (fq.size() != 0));
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Czas Wykonanie Algorytmu Schrange " << duration << "ms" << std::endl;
    }
}
void PQ::PrintProcesses() {
    std::cout << "Wartosci Procesow: " << std::endl;
    for (auto i : ProcessInOrder) {
        for (auto j : i) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
}
void PQ::CMAX() {
    int endtime = 0;
    int cmax = 0;
    int starttime = 0;
    std::vector<int> foo;
    foo = ProcessInOrder[0];
    starttime = foo[0] + foo[1];
    for (int i = 1; i < ProcessInOrder.size(); i++) {
        starttime = cmax;
        foo = ProcessInOrder[i];
        if (foo[0] <= starttime) {
            cmax = starttime + foo[1];
            if (endtime < (cmax + foo[2])) {
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
void PQ::Order() {
    std::cout << "Kolejnosc: " << std::endl;
    for (std::vector<int> i : ProcessInOrder) {
        std::cout << i[numberOfParameters] << " ";
    }
    std::cout << std::endl;
}