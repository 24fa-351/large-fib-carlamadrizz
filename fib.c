#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
long long fib_recursive(int n);
long long fib_iterative(int n);
long long fib_cache(int n);

// Function definitions

// Modified fib_recursive function
long long fib_recursive(int n) {
    if (n == 1) {
        return 0;  
    }
    if (n == 2) {
        return 1;
    }
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// Modified fib_iterative function
long long fib_iterative(int n) {
    long long a = 0, b = 1, next;
    if (n == 1) return 0;
    if (n == 2) return b;

    for (int i = 3; i <= n; i++) {
        next = a + b;
        a = b;
        b = next;
    }
    return b;
}

// Helper function for the cache-based Fibonacci method
long long fib_cache_helper(int n, long long *cache) {
    if (cache[n] != -1) {
        return cache[n];
    }
    if (n == 1) {
        cache[n] = 0;
    } else if (n == 2) {
        cache[n] = 1;
    } else {
        cache[n] = fib_cache_helper(n - 1, cache) + fib_cache_helper(n - 2, cache);
    }
    return cache[n];
}

// Modified fib_cache function
long long fib_cache(int n) {
    long long *cache = (long long *)malloc((n + 1) * sizeof(long long));
    if (cache == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i <= n; i++) {
        cache[i] = -1;
    }
    long long result = fib_cache_helper(n, cache);
    free(cache);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <integer> <r/i/c>\n", argv[0]);
        return 1;
    }

    // Get input number from command-line argument
    int input_number = atoi(argv[1]);

    long long fib;

    // Determine which Fibonacci function to use based on the second argument
    if (strcmp(argv[2], "r") == 0) {
        fib = fib_recursive(input_number);
    } else if (strcmp(argv[2], "i") == 0) {
        fib = fib_iterative(input_number);
    } else if (strcmp(argv[2], "c") == 0) {
        fib = fib_cache(input_number);
    } else {
        printf("Second argument must be 'r', 'i', or 'c'\n");
        return 1;
    }

    printf("%lld", fib);

    return 0;
}
