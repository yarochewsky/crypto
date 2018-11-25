#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * all_primes - prints all prime numbers up to n
 * @n : upperbound limit of primes to be printed
 *      (n is potentially the last prime)
 *      n > 1
 * Returns 1/0 on success/failure
*/
int all_primes(int n);

int main(int argc, char** argv) {
    int x;
    printf("Enter the maximum prime you want to print numbers: ");
    scanf("%d", &x);
    all_primes(x);
    return 0;
}

/** 
 * Implements Sieve of Eratosthenes
 * https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
*/
int all_primes(int n) {
    if (n <= 1) return 0;
    int* arr = (int*) malloc(sizeof(int) * n);
    if (!arr) return 0;
    for (int i = 2; i < n; i++) {
        arr[i] = 1;            
    }
    int sqrt_n = round(sqrt(n));
    for (int i = 2; i < sqrt_n; i++) {
        if (arr[i]) {
            int x = 0;
            for (int j = i * i; j < n; j += i) {
                arr[j] = 0; 
                x++;
            }
        }
    }
    // 2 is the first prime
    printf("%d", 2);
    for (int i = 3; i < n; i++) {
        if (arr[i]) {
            printf(",%d", i);
        }
    }
    printf("\n");
    // free arry and be done
    free(arr);
    return 1;
}
