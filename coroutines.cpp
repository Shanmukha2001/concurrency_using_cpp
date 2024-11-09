#include <coroutine>
#include <iostream>

template<typename T>
struct Generator {
    struct promise_type {
        T value;
        auto get_return_object() { return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) }; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T val) { value = val; return {}; }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

    using handle_type = std::coroutine_handle<promise_type>;
    handle_type coro;

    Generator(handle_type h) : coro(h) {}
    ~Generator() { if (coro) coro.destroy(); }
    Generator(Generator&& other) noexcept : coro(other.coro) { other.coro = nullptr; }

    T getValue() const { return coro.promise().value; }
    bool next() { coro.resume(); return !coro.done(); }
};

Generator<int> getNext(int start = 0, int step = 1) {
    for (int value = start;; value += step)
        co_yield value;
}

int main() {
    int i =0;
    for (auto gen = getNext(0, 2); gen.next(),i<10;i++)
        std::cout << gen.getValue() << " ";
    std::cout << std::endl;
}
