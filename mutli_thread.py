import threading
import time

NUM_THREADS = 10
STEP = 1_000_000
partial_sums = [0] * NUM_THREADS


def compute_sum(thread_index, start, end):
    local_sum = 0
    # Using an explicit loop to match the C workload step-for-step
    for i in range(start, end + 1):
        local_sum += i
    partial_sums[thread_index] = local_sum


def main():
    threads = []
    start_time = time.perf_counter()

    # Create and start all 10 threads
    for i in range(NUM_THREADS):
        start_val = (i * STEP) + 1
        end_val = (i + 1) * STEP
        t = threading.Thread(target=compute_sum, args=(i, start_val, end_val))
        threads.append(t)
        t.start()

    # Wait for all threads to complete
    for t in threads:
        t.join()

    total_sum = sum(partial_sums)
    end_time = time.perf_counter()

    print(f"Total Sum: {total_sum}")
    print(f"Time taken in Python: {end_time - start_time:.6f} seconds")


if __name__ == "__main__":
    main()