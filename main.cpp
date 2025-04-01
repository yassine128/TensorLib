#include <iostream>
#include "Tensor.cpp"
#include <chrono>

int main() {
    Tensor tensor1(1, 2);
    Tensor tensor2(1, 4);

    auto start = std::chrono::high_resolution_clock::now();
    Tensor tadd = tensor1 * tensor2; 
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken: " << duration.count() << " microseconds\n";

    std::cout << tensor1 << std::endl;
    std::cout << tensor2 << std::endl;
    std::cout << tadd << std::endl;

    return 0; 
}