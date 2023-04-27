#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define srand48(x) srand((int)(x))
#define drand48() ((double)rand()/RAND_MAX)

void monteCarlo(int N, int K)
{
    // координаты случайной точки
    double x, y;
    // расстояние до центра от этой точки
    double d;

    // кол-во точек внутри круга
    int pCircle = 0;

    // внутри квадрата
    int pSquare = 0;

    int i = 0;

#pragma omp parallel firstprivate(x, y, d, i) reduction(+ : pCircle, pSquare) num_threads(K)
    {
        // инициализируем случайную точку
        srand48((int)time(NULL));
        // по N точек в каждой ветке
        for (i = 0; i < N; i++) {
            x = (double)drand48();
            y = (double)drand48();

            d = ((x * x) + (y * y));

            if (d <= 1) {
                pCircle++;
            }

            pSquare++;
        }
    }
    double pi = 4.0 * ((double)pCircle / (double)(pSquare));
    printf("Final Estimation of Pi = %f\n", pi);
}

int main()
{
    int N = 10000;
    int K = 5;
    monteCarlo(N, K);
}