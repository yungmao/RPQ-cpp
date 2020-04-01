#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>

//#define FILEPATH "C:\\Users\\Student241165\\source\\repos\\RPQ\\Text.txt"
#define FILEPATH "C:\\Users\\Student241165\\Desktop\\RPQ\\data10.txt"

class RPQ {
public:
    RPQ() {
        loadFile();
        SortCarlier(VectorOfProcesses);
        //SortSchrangePMTN(VectorOfProcesses);
        //CMAX();
    }
private:
    std::vector<std::vector<int>> VectorOfProcesses;
    std::vector<std::vector<int>> PSchrange;
    std::vector<std::vector<int>> PMSchrange;
    std::vector<std::vector<int>> VCar;
    std::vector<int> Process;
    int numberOfProcess = 0;
    int numberOfParameters = 0;
    int buffer;
    std::vector<int> wykonaneProcesy;
public:
    void loadFile();
    void PrintProcesses();
    int CMAX(std::vector<std::vector<int>> V);
    void SortByR();
    void SortByQR();
    void SortCarlier(std::vector<std::vector<int>> VOP);
    void SortSchrange(std::vector<std::vector<int>> V);
    void Order();
    void SortSchrangePMTN(std::vector<std::vector<int>> V);
    int U;
    int UB=INT_MAX;
    int LB;
    int a;
    int b;
    int c=-1;
    int lastone;
    void znajdza();
    void znajdzb();
    void znajdzc();
};
//Sorting functions
bool QR(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    return (vec1[2] + vec1[0] < vec2[2] + vec2[0]);
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
            Process.push_back(j + 1);
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
    std::sort(VectorOfProcesses.begin(), VectorOfProcesses.end(), R);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Czas Wykonania funkcji sort R: " << duration << "ms" << std::endl;
}
int RPQ::CMAX(std::vector<std::vector<int>> V) {
    int endtime = 0;
    int cmax = 0;
    int starttime = 0;
    int endingprocess = 0;
    std::vector<int> foo;
    foo = V[0];
    starttime = foo[0] + foo[1];
    for (int i = 1; i < V.size(); i++) {
        starttime = cmax;
        foo = V[i];
        if (foo[0] <= starttime) {
            cmax = starttime + foo[1];
            if (endtime < (cmax + foo[2])) {
                endtime = cmax + foo[2];
                endingprocess = foo[3];
            }
        }
        else
        {
            starttime = starttime + (foo[0] - starttime);
            cmax = starttime + foo[1];
            if (endtime < (cmax + foo[2])) {
                endtime = cmax + foo[2];
                endingprocess = foo[3];
            }
        }
    }
    lastone = endingprocess;
   // std::cout << "Wynik CMAX = " << endtime << std::endl;
    return endtime;
}
void RPQ::SortByQR() {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::sort(VectorOfProcesses.begin(), VectorOfProcesses.end(), QR);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Czas Wykonania funkcji sort RQ: " << duration << "ms" << std::endl;
}
void RPQ::SortSchrange(std::vector<std::vector<int>> V) {
    std::vector<std::vector<int>> Vfoo;
    std::vector<std::vector<int>> VFinal;
    std::vector<int> foo;
    std::sort(V.begin(), V.end(), R);
    foo = V[0];
    int time = foo[0];
    auto t1 = std::chrono::high_resolution_clock::now();
    std::sort(V.begin(), V.end(), ReverseR);
    do {
        do {
            if (V.size() != 0) {
                foo = V[V.size() - 1];
                if (foo[0] <= time) {
                    Vfoo.push_back(foo);
                    V.pop_back();
                }
            }
            if ((Vfoo.size() == 0)) {
                time = foo[0];
            }
        } while ((V.size() > 0) && (foo[0] <= time));
        std::sort(Vfoo.begin(), Vfoo.end(), Q);
        foo = Vfoo[Vfoo.size() - 1];
        time += foo[1];
        VFinal.push_back(foo);
        Vfoo.pop_back();
    } while ((V.size() != 0) || (Vfoo.size() != 0));
    V = VFinal;
    auto t2 = std::chrono::high_resolution_clock::now();
    PSchrange = V;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    //std::cout << "Czas Wykonanie Algorytmu Schrange " << duration << "ms" << std::endl;
}
void RPQ::Order() {
    std::cout << "Kolejnosc: " << std::endl;
    for (std::vector<int> i : VectorOfProcesses) {
        std::cout << i[numberOfParameters] << " ";
    }
}
void RPQ::SortSchrangePMTN(std::vector<std::vector<int>> V) {
    std::vector<std::vector<int>> Vfoo;
    std::vector<std::vector<int>> VFinal;
    std::vector<int> NFinished;
    std::vector<int> foo;
    std::vector<int> exec;
    std::sort(V.begin(), V.end(), R);
    foo = V[0];
    int time = foo[0];
    int kolejnosc = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    std::sort(V.begin(), V.end(), ReverseR);
    do {
        do {
            if (V.size() != 0) {
                foo = V[V.size() - 1];
                if (foo[0] <= time) {
                    Vfoo.push_back(foo);
                    V.pop_back();
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
        } while ((V.size() > 0) && (foo[0] <= time));
        std::sort(Vfoo.begin(), Vfoo.end(), Q);
        foo = Vfoo[Vfoo.size() - 1];
        time += foo[1];
        VFinal.push_back(foo);
        exec = foo;
        ++kolejnosc;
        Vfoo.pop_back();
    } while ((V.size() != 0) || (Vfoo.size() != 0));
    V = VFinal;
    auto t2 = std::chrono::high_resolution_clock::now();
    PMSchrange = V;
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
   // std::cout << "Czas Wykonanie Algorytmu Schrange PMTN: " << duration << "ms" << std::endl;
}
void RPQ::znajdza() {
    std::vector<int> foo = VectorOfProcesses[b];
    std::vector<int> foo1 = VectorOfProcesses[b];
    int skladnik = foo[2];
    int suma = 0, i;
    // najmniejsze takie a, czyli trzeba iœæ od lewej
    for (int _a = 0; _a < b; _a++)
    {
        foo1 = VCar[_a];
        suma = 0;
        for (i = _a; i <= b; i++) {
            foo = VCar[i];
            suma += foo[1];
        }
        if (CMAX(PSchrange) == (foo1[0] + suma + skladnik)) {
            a = _a;
        }
    }
}
void RPQ::znajdzb()
{
}
void RPQ::znajdzc() {
    std::vector<int> foo = VectorOfProcesses[b];
    int porownanie = foo[2];
    int i;
    c = -1;
    for (i = b; i >= a; i--)
    {
        foo = PSchrange[i];
        if (foo[2] < porownanie)
        {
            c = i;
            break;
        }
    }
}

void RPQ::SortCarlier(std::vector<std::vector<int>> VOP) {
    std::vector<std::vector<int>> K;
    std::vector<int> foo;
    std::vector<int> foo_C;
    int r_plim=INT_MAX; // nowe r dla zadania c
    int p_plim=0; // suma p KROK 5
    int q_plim=INT_MAX; // nowe q dla zadania c
    auto t1 = std::chrono::high_resolution_clock::now();
    SortSchrange(VOP);
    U = CMAX(PSchrange);
    VCar = PSchrange;
    if (U < UB) {
        UB = U;
    }
    znajdza();
    znajdzc();
    if (c == -1) 
    {
        std::cout << "\tNie znaleziono zadania c!!!\n";
        return;
    }
    foo_C = VectorOfProcesses[c];
    for (int i = c + 1; i <= b; i++) {
        foo = VectorOfProcesses[i];
        if (r_plim > foo[0]) {
            r_plim = foo[0];
        }
        if (q_plim > foo[2]) {
            q_plim = foo[2];
        }
        p_plim += foo[1];
    }
    foo = foo_C;
    if (r_plim > foo_C[0]) {
        foo[0] = r_plim;
        VectorOfProcesses[c - 1] = foo;
    }
    SortSchrangePMTN(VOP);
    LB = CMAX(PMSchrange);
    if (LB < UB) {
        SortCarlier(VOP);
    }
    foo = foo_C;
    VectorOfProcesses[c-1] = foo;
    if (q_plim > foo_C[2]) {
        foo[2] = q_plim;
        VectorOfProcesses[c - 1] = foo;
    }
    LB = CMAX(PMSchrange);
    if (LB < UB) {
        SortCarlier(VOP);
    }
    foo = foo_C;
    VectorOfProcesses[c - 1] = foo;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Czas Wykonanie algorytmy Carliera: " << duration << "ms" << std::endl;
}