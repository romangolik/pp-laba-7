#include <iostream>
#include <omp.h>

long findArraySum(long mas[], int size) {
    do {
        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < size / 2; i++) {
                #pragma omp atomic
                mas[i] = mas[i] + mas[size - i - 1];
            }
        }

        size = size / 2 + size % 2;
    } while (size > 1);

    return mas[0];
}

int main() {
    int size = 10000;
    int mas[size];

    omp_set_num_threads(10);

    for (int i = 0; i < size; i++)
        mas[i] = i;

    std::cout << findArraySum(reinterpret_cast<long *>(mas), size) << std::endl;
    return 0;
}
