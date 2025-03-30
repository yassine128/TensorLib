#ifndef TENSOR_CPP
#define TENSOR_CPP

#include <tuple>
#include <vector>
#include <random>
#include <iostream>
#include <cassert>


class Tensor {
    public: 
        Tensor(int cols, int rows) : rows_(rows), cols_(cols), tensor_(rows * cols, 0.0f) {
            initializeTensor(); 
        }

        void initializeTensor(float min = 0.0f, float max = 1.0f) {
            static std::random_device rd;
            static std::mt19937 rng(rd());
            std::uniform_real_distribution<float> dist(min, max);

            for (auto& val : tensor_) {
                val = dist(rng);
            }
        }

        std::tuple<int, int> shape() {
            return {rows_, cols_};
        }

        float& operator()(int i, int j) {
            return tensor_[i * cols_ + j];
        }

        const std::vector<float>& data() const {
            return tensor_;
        }

        friend std::ostream& operator<<(std::ostream& stream, Tensor tensor) {
            stream << "["; 
            for (auto& val : tensor.getTensor()) {
                stream << std::to_string(val) + ", ";
            }
            stream << "]";
            return stream;
        } 

        Tensor operator+(const Tensor& other) {
            assert(tensor_.size() == other.tensor_.size());
            auto [rows, cols] = shape();
            Tensor tadd(rows, cols);

            for (auto i = 0; i < tensor_.size(); ++i) {
                tadd.tensor_[i] = other.tensor_[i] + tensor_[i];
            }

            return tadd; 
        }

    private:
        std::vector<float>& getTensor() { 
            return tensor_; 
        }

        std::vector<float> tensor_;
        int rows_, cols_; 
};

#endif // TENSOR_CPP