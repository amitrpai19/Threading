import time


def compute_sum_single_thread():
    start_time = time.perf_counter()

    total_sum = 0
    # Summing 1 to 10,000,000 in a single sequential loop
    for i in range(1, 10_000_001):
        total_sum += i

    end_time = time.perf_counter()

    print(f"Total Sum: {total_sum}")
    print(
        f"Time taken (Single-Threaded): {end_time - start_time:.6f} seconds"
    )


if __name__ == "__main__":
    compute_sum_single_thread()