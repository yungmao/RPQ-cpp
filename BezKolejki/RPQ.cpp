﻿#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>

#define FILEPATH "C:\\Users\\Student241165\\source\\repos\\RPQ\\Text.txt"
//#define FILEPATH "C:\\Users\\Student241165\\Desktop\\RPQ\\data10.txt"

class RPQ {
public:               
    RPQ() {
        loadFile();
       /*
        CMAX();
        SortByR();
        CMAX();
        PrintProcesses();
        SortByQR();
        CMAX();
        PrintProcesses();
        */
        
        SortSchrange();
       CMAX();
     // PrintProcesses();
       Order();
       
        SortSchrangePMTN();
        CMAX();
      //PrintProcesses();
        Order();
    }
private:
    std::vector<std::vector<int>> VectorOfProcesses;
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
//Sorting functions
bool QR(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    return (vec1[2]+vec1[0] < vec2[2]+vec2[0]);
}
bool Q(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    return (vec1[2] < vec2[2]);
}
bool R(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    return (vec1[0] < vec2[0]);
}
bool ReverseR(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    return (vec1[0] > vec2[0]);
}
//Main Function
int main() {
    RPQ rpq;
    //rpq.PrintProcesses();
    //return 0;
}

// Definig methods
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
            Process.push_back(j+1);
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
    std::sort(VectorOfProcesses.begin(), VectorOfProcesses.end(),R);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Czas Wykonania funkcji sort R: " << duration << "ms" << std::endl;
}
void RPQ::CMAX() {
    int endtime = 0;
    int cmax = 0;
    int starttime = 0;
    std::vector<int> foo;
    foo = VectorOfProcesses[0];
    starttime = foo[0] + foo[1];
    for (int i = 1; i < VectorOfProcesses.size(); i++) {
        starttime = cmax;
        foo = VectorOfProcesses[i];
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
void RPQ::SortByQR() {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::sort(VectorOfProcesses.begin(), VectorOfProcesses.end(),QR);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Czas Wykonania funkcji sort RQ: " << duration << "ms" << std::endl;
}
void RPQ::SortSchrange() {
    std::vector<std::vector<int>> Vfoo;
    std::vector<std::vector<int>> VFinal;
    std::vector<int> foo;
    std::sort(VectorOfProcesses.begin(), VectorOfProcesses.end(), R);
    foo = VectorOfProcesses[0];
    int time = foo[0];
    auto t1 = std::chrono::high_resolution_clock::now();
    std::sort(VectorOfProcesses.begin(), VectorOfProcesses.end(), ReverseR);
    do {
        do {
            if (VectorOfProcesses.size() != 0) {
                foo = VectorOfProcesses[VectorOfProcesses.size() - 1];
                if (foo[0] <= time) {
                    Vfoo.push_back(foo);
                    VectorOfProcesses.pop_back();
                }
            }
            if ((Vfoo.size()==0)) {
                    time = foo[0];
            }
        } while((VectorOfProcesses.size()>0) && (foo[0]<=time));
        std::sort(Vfoo.begin(), Vfoo.end(),Q);
        foo = Vfoo[Vfoo.size() - 1];
        time += foo[1];
        VFinal.push_back(foo);
        Vfoo.pop_back();
    } while ((VectorOfProcesses.size() != 0) || (Vfoo.size() != 0));
    VectorOfProcesses = VFinal;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Czas Wykonanie Algorytmu Schrange " << duration << "ms" << std::endl;
}
void RPQ::Order() {
    std::cout << "Kolejnosc: " << std::endl;
    for (std::vector<int> i : VectorOfProcesses) {
        std::cout << i[numberOfParameters] << " ";
    }
}
void RPQ::SortCarlier() {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Czas Wykonanie algorytmy Carliera: " << duration << "ms" << std::endl;
}
void RPQ::SortSchrangePMTN() {
    std::vector<std::vector<int>> Vfoo;
    std::vector<std::vector<int>> VFinal;
    std::vector<int> NFinished;
    std::vector<int> foo;
    std::vector<int> exec;
    std::sort(VectorOfProcesses.begin(), VectorOfProcesses.end(), R);
    foo = VectorOfProcesses[0];
    int time = foo[0];
    int kolejnosc = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    std::sort(VectorOfProcesses.begin(), VectorOfProcesses.end(), ReverseR);
    do {
        do {
            if (VectorOfProcesses.size() != 0) {
                foo = VectorOfProcesses[VectorOfProcesses.size() - 1];
                if (foo[0] <= time) {
                    Vfoo.push_back(foo);
                    VectorOfProcesses.pop_back();
                    if (kolejnosc != 0) {
                        if (foo[2] > exec[2]) {
                            NFinished = exec;
                            exec[1] = time - foo[0];
                            NFinished[1] -= exec[1];
                            time = foo[0];
                            VFinal.pop_back();
                            VFinal.push_back(NFinished);
                            if (exec[1] > 0) {
                                Vfoo.push_back(exec);
                            }
                        }
                    }
                }
            }
            if ((Vfoo.size() == 0)) {
                time = foo[0];
            }
        } while ((VectorOfProcesses.size() > 0) && (foo[0] <= time));
        std::sort(Vfoo.begin(), Vfoo.end(), Q);
        foo = Vfoo[Vfoo.size() - 1];
        time += foo[1];
        VFinal.push_back(foo);
        exec = foo;
        ++kolejnosc;
        Vfoo.pop_back();
    } while ((VectorOfProcesses.size() != 0) || (Vfoo.size() != 0));
    VectorOfProcesses = VFinal;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Czas Wykonanie Algorytmu Schrange PMTN: " << duration << "ms" << std::endl;
}