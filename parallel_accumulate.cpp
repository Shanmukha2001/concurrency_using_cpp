#include <bits/stdc++.h>
using namespace std;

#define MIN_BLOCK_SIZE 1000

// Custom accumulate function to avoid name conflict with std::accumulate
template<typename iterator, typename T>
void custom_accumulate(iterator start, iterator end, T &ref) {
    ref = std::accumulate(start, end, 0);
}

template<typename iterator, typename T>
T parallel_accumulate(iterator start, iterator end, T &ref) {
    int input_size = distance(start, end);
    int required_threads = (input_size + 1) / MIN_BLOCK_SIZE;
    int available_threads = thread::hardware_concurrency();
    int num_threads = min(required_threads, available_threads);
    int block_size = (input_size + 1) / num_threads;

    vector<T> results_of_threads(num_threads);
    vector<thread> threads(num_threads - 1); // excluding main thread
    iterator last;

    // Spawn threads to process blocks in parallel
    for (int i = 0; i < num_threads - 1; i++) {
        last = start;
        advance(last, block_size);
        threads[i] = thread([=, &results_of_threads]() {
            custom_accumulate(start, last, results_of_threads[i]);
        });
        start = last; // Update start for the next block
    }

    // Process the remaining block in the main thread
    custom_accumulate(start, end, results_of_threads[num_threads - 1]);

    // Join all threads
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    // same as
    // for (auto& t : threads) {
    //    t.join();
    // }


    // Accumulate all partial results into ref
    ref = accumulate(results_of_threads.begin(), results_of_threads.end(), 0);
    return ref;
}

int main() {
    const int size = 8000;
    int *my_arr = new int[size];
    int ref = 0;
    srand(0);

    // Initialize array with random values
    for (size_t i = 0; i < size; i++) {
        my_arr[i] = rand() % 10;
    }

    // Call parallel_accumulate and display result
    int result = parallel_accumulate<int*, int>(my_arr, my_arr + size, ref);
    cout << result << endl;

    delete[] my_arr;
    return 0;
}
