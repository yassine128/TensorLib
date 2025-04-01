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

            int size = tensor_.size(); 
            for (int i = 0; i < size; ++i) {
                tadd.tensor_[i] = tensor_[i] + other.tensor_[i];
            }

            return tadd; 
        }
        
        Tensor operator-(const Tensor& other) {
            assert(tensor_.size() == other.tensor_.size());
            auto [rows, cols] = shape();
            Tensor tsub(rows, cols);

            int size = tensor_.size(); 
            for (int i = 0; i < size; ++i) {
                tsub.tensor_[i] = tensor_[i] - other.tensor_[i];
            }

            return tsub; 
        }

        Tensor operator*(Tensor& other) {
            int thisSize = tensor_.size(); 
            int otherSize = other.tensor_.size();

            assert(thisSize == otherSize || !(thisSize % otherSize) || !(otherSize % thisSize));
            auto [rowsThis, colsThis] = shape();
            auto [rowsOther, colsOther] = other.shape();
            int max_rows = std::max(rowsThis, rowsOther);
            int max_cols = std::max(colsThis, colsOther);
            Tensor tmul(max_rows, max_cols);

            int maxIterSize = std::max(thisSize, otherSize); 

            for (int i = 0; i < maxIterSize; ++i) {
                tmul.tensor_[i] = tensor_[i % thisSize] * other.tensor_[i % otherSize];
            }

            return tmul; 
        }

        Tensor operator/(Tensor& other) {
            int thisSize = tensor_.size(); 
            int otherSize = other.tensor_.size();

            assert(thisSize == otherSize || !(thisSize % otherSize) || !(otherSize % thisSize));
            auto [rowsThis, colsThis] = shape();
            auto [rowsOther, colsOther] = other.shape();
            int max_rows = std::max(rowsThis, rowsOther);
            int max_cols = std::max(colsThis, colsOther);
            Tensor tmul(max_rows, max_cols);

            int maxIterSize = std::max(thisSize, otherSize); 

            for (int i = 0; i < maxIterSize; ++i) {
                tmul.tensor_[i] = tensor_[i % thisSize] / other.tensor_[i % otherSize];
            }

            return tmul; 
        }

        Tensor matMul(Tensor& other) {
            auto [rowsThis, colsThis] = shape();
            auto [rowsOther, colsOther] = other.shape();

            assert(colsThis == rowsOther); 
            Tensor mat(rowsThis, colsOther);

            for (int i = 0; i < rowsThis; ++i) {
                for (int j = 0; j < colsOther; ++j) {
                    mat(i, j) = 0;
                }
            }

            for (int i = 0; i < rowsThis; ++i) {
                for (int j = 0; j < colsOther; ++j) {
                    for (int k = 0; k < colsThis; ++k) {
                        mat(i, j) += this->operator()(i, k) * other(k, j);
                    }
                }
            }

            return mat; 
        }

    private:
        std::vector<float>& getTensor() { 
            return tensor_; 
        }

        std::vector<float> tensor_;
        int rows_; 
        int cols_; 
};

#endif // TENSOR_CPP