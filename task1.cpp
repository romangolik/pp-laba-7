#include <iostream>
#include <omp.h>

long findPartSum(const int mas[], int begin, int end) {
    long partSum = 0;
    for (int i = begin; i <= end; i++) {
        partSum += mas[i];
    }
    return partSum;
}

int main() {
    int size = 10000;
    int mas[size];
    long SumMas = 0;

    for (int i = 0; i < size; i++)
        mas[i] = i;

    int NumThreads = 10;

    omp_set_num_threads(NumThreads);

    int beginMas[NumThreads];
    int endMas[NumThreads];
    for (int i = 0; i < NumThreads; i++)
        beginMas[i] = size / NumThreads * i;
    for (int i = 0; i < NumThreads - 1; i++)
        endMas[i] = beginMas[i + 1] - 1;

    endMas[NumThreads - 1] = size - 1;

    #pragma omp parallel reduction(+: SumMas)
    {
        #pragma omp for
        for (int i = 0; i < NumThreads; i++) {
            SumMas += findPartSum(mas, beginMas[i], endMas[i]);
        }
    }

    std::cout << SumMas << std::endl;

    return 0;
}
