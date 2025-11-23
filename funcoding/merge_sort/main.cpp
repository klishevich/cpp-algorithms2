#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

template<typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "Vector (" << vec.size() << " elements): ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void merge(int *pL, int *pR, int *pA, int i, int j, int a, int b) {
    if (a < b) {
        if ((j <= 0 || i > 0) && pL[i-1] > pR[j-1]) {
            pA[b-1] = pL[i-1];
            i = i-1;
        } else {
            pA[b-1] = pR[j-1];
            j=j-1;
        }
        merge(pL, pR, pA, i, j, a, b-1);
    }
}

void merge_sort(int *pA, int a, int b) {
    if (1 < b - a) {
        int c = (a + b + 1) / 2;
        merge_sort(pA, a, c);
        merge_sort(pA, c, b);
        vector<int> vL;
        vL.reserve(c-a);
        for (int i=0; i<c-a;++i) {
            vL.push_back(*(pA+a+i));
        }
        vector<int> vR;
        vR.reserve(b-c);
        for (int i=0; i<b-c;++i) {
            vR.push_back(*(pA+c+i));
        }
        merge(&vL[0], &vR[0], pA, c-a, b-c, a, b);
    }
}

int main(int argc, char const *argv[])
{
    // vector<int> vInput { 2, 4, 6, 7, 1, 3, 9, 10 };
    // size_t size = vInput.size();
    // size_t half = size / 2;
    // vector<int> vResult(size, -1);
    // printVector(vInput);
    // merge(&vInput[0], &vInput[half], &vResult[0], half, half, 0, size);
    // printVector(vResult);

    vector<int> vInput { 7, 5, 3, 1, 6, 4, 2, 0 };
    printVector(vInput);
    merge_sort(vInput.data(), 0, vInput.size());
    printVector(vInput);
    return 0;
}


