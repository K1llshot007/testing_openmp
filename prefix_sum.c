#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>


#define n 2000000000
#define numThreads 10

void computePrefixSum(size_t* input, size_t* output){
    size_t divisionOfLabor = n/numThreads;
    size_t *tempArray = malloc((numThreads+1)*sizeof(size_t)); // Used for parallel section
    size_t sum = 0;
    size_t x =0;
    #pragma omp parallel 
    {

        #pragma omp single
        {
            int nthr = omp_get_num_threads();

        }
        int tid = omp_get_thread_num();




        #pragma omp for schedule(static)
        for (size_t i = 0; i < n; i++){
                sum+= input[i];

                output[i] = sum;
                
                
        }
        tempArray[tid+1] = sum;
        #pragma omp barrier

        for (int i = 0; i < (tid+1); i++)
        {
            x += tempArray[i];
        }
         

        #pragma omp for schedule(static)
        for (size_t i = 0; i < n; i++)
        {
            output[i] += x ;
        }
        

        
    }
    free(tempArray);

}





int main() {
    size_t *inputArray = malloc(n*sizeof(size_t));
    size_t *resultArray = malloc(n*sizeof(size_t));

    for (size_t i = 0; i < n; i++)
    {
        inputArray[i] = rand();
    }

    // size_t sum = 0;
    
    srand(time(NULL));
    double elt = omp_get_wtime(); //start of timer

    // #pragma omp parallel for reduction (+:sum)
    // for (size_t i = 0; i < n; i++)
    // {
    //     sum+= inputArray[i];

    //     resultArray[i] = sum;

    // }

    computePrefixSum(inputArray, resultArray);
    





    elt = omp_get_wtime() - elt; // stop of timer


    printf("Time taken: %.3lf seconds\n", elt);
    printf("Performance rate: %.3lf GFLOPS\n", (6.0 * n * 1e-9)/elt);


    free(inputArray);
    free(resultArray);
    return 0;
}
