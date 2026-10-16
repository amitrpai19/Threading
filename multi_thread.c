// compiler command - gcc -O0 mutli_thread.c -o multi_thread

#include <stdio.h>
#include <windows.h>

#define NUM_THREADS 10
#define STEP 1000000

// Structure to pass range and store the partial sum for each thread
typedef struct {
    long long start;
    long long end;
    long long partial_sum;
} ThreadData;

// Windows thread function signature requires DWORD WINAPI and LPVOID
DWORD WINAPI compute_sum(LPVOID arg) {
    ThreadData* data = (ThreadData*)arg;
    long long sum = 0;
    for (long long i = data->start; i <= data->end; i++) {
        sum += i;
    }
    data->partial_sum = sum;
    return 0;
}

int main() {
    HANDLE threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    long long total_sum = 0;

    // Windows high-resolution timer variables
    LARGE_INTEGER frequency, start_time, end_time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);

    // Spawn all 10 threads concurrently
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = (i * STEP) + 1;
        thread_data[i].end = (i + 1) * STEP;
        thread_data[i].partial_sum = 0;

        threads[i] = CreateThread(
            NULL,               // Default security attributes
            0,                  // Default stack size
            compute_sum,        // Thread function name
            &thread_data[i],    // Argument to thread function
            0,                  // Run immediately upon creation
            NULL                // Thread ID not needed
        );
    }

    // Wait for all 10 threads to finish
    WaitForMultipleObjects(NUM_THREADS, threads, TRUE, INFINITE);

    // Combine partial sums and close thread handles
    for (int i = 0; i < NUM_THREADS; i++) {
        total_sum += thread_data[i].partial_sum;
        CloseHandle(threads[i]);
    }

    QueryPerformanceCounter(&end_time);
    double time_taken = (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;

    printf("Total Sum: %lld\n", total_sum);
    printf("Time taken in C (Windows): %.6f seconds\n", time_taken);

    return 0;
}