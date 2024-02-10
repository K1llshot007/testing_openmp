#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>



int main() {

    const size_t n = 20000;
    size_t i =0;
    size_t sum[20000];
    srand(time(NULL));
    size_t input[20000];
    size_t x;
    size_t j =0;
    for( j;j<n;j++){
        input[j] = rand();
    }
    sum[0] = input[0];
    x = input[0];
    double elt = omp_get_wtime();
   i =1;
    #pragma omp parallel shared(input,i) private(sum)
   while(i<20000){
    
    x+= input[i];
    #pragma omp critical
    {
        
    sum[i] = x;
    i++;
    }
   }


    elt = omp_get_wtime() - elt;


    printf("Time taken: %.3lf seconds\n", elt);
    printf("Performance rate: %.3lf GFLOPS\n", (6.0 * n * 1e-9)/elt);

    return 0;
}
