#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>


#define n 2000000000


int main() {
    size_t *inputArray = malloc(n*sizeof(size_t));
    size_t *resultArray = malloc(n*sizeof(size_t));


    for (size_t i = 0; i < n; i++)
    {
        inputArray[i] = rand();
    }

    size_t sum = 0;
    
    srand(time(NULL));
    double elt = omp_get_wtime(); //start of timer


    for (size_t i = 0; i < n; i++)
    {
        sum+= inputArray[i];

        resultArray[i] = sum;

    }
    





    elt = omp_get_wtime() - elt; // stop of timer


    printf("Time taken: %.3lf seconds\n", elt);
    printf("Performance rate: %.3lf GFLOPS\n", (6.0 * n * 1e-9)/elt);

    return 0;
}
