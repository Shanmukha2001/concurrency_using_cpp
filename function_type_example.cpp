#include <iostream>
#include <vector>
#include <algorithm>

// Function template to apply a function to each element of a vector
template<typename FunctionType>
void applyToVector(const std::vector<int>& vec, FunctionType func) {
    for (const auto& element : vec) {
        func(element);  // Call the passed function on each element
    }
}

// Example function to print an element
void printElement(int element) {
    std::cout << element << " ";
}

// Example function to square an element and print it
void squareAndPrint(int element) {
    std::cout << (element * element) << " ";
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "Printing elements: ";
    applyToVector(numbers, printElement);  // Using print function
    std::cout << "\n";

    std::cout << "Squaring elements: ";
    applyToVector(numbers, squareAndPrint); // Using square function
    std::cout << "\n";

    return 0;
}
