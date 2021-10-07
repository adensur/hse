#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

#include <iostream>
#include <sstream>

#include <random>

class TPrefixArray {
public:
    TPrefixArray(const std::vector<int>& vec);
    long long CalcSum(size_t leftIndex, size_t rightIndex) const;
private:
    std::vector<long long> Data_;
};

TPrefixArray::TPrefixArray(const std::vector<int>& vec) {
    Data_.reserve(vec.size() + 1);
    long long sum = 0;
    Data_.push_back(sum);
    for (size_t i = 0; i < vec.size(); ++i) {
        sum += vec[i];
        Data_.push_back(sum);
    }
}

long long TPrefixArray::CalcSum(size_t leftIndex, size_t rightIndex) const {
    return Data_[rightIndex] - Data_[leftIndex];
}


std::vector<int> GenerateVector(size_t size, int max) {
    std::vector<int> result;
    result.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        int r = rand() % max;
        result.push_back(r);
    }
    return result;
}

std::string ToString(const std::vector<int>& vec) {
    std::stringstream ss;
    for (size_t i = 0; i < vec.size(); ++i) {
        ss << vec[i] << " ";
    }
    return ss.str();
}

long long NaiveCalcSum(const std::vector<int> vec, size_t start, size_t end) {
    if (start < 0 || start >= vec.size() || end <= 0 || end > vec.size()) {
        std::cerr << "start, end, vec.size: " << start << " " << end << " " << vec.size() << std::endl;
        throw std::runtime_error("Invalid inputs for NaiveCalcSum");
    }
    long long sum = 0;
    for (size_t i = start; i < end; ++i) {
        sum += vec[i];
    }
    return sum;
}

int TestMain() {
    size_t i = 0;
    {
        ++i;
        std::vector<int> vec = {1, 5, 9, 6, 8, 4, 3};
        TPrefixArray array(vec);
        int j = 0;
        {
            ++j;
            int start = 3;
            int end = 6;
            int computedSum = array.CalcSum(start, end);
            int realSum = 18;
            if (realSum != computedSum) {
                std::cerr << "error in test " << i << " case " << j << "; expected " << realSum << " got " << computedSum << std::endl;
                std::cerr << "start: " << start << "; end: " << end << "; vec: " << ToString(vec) << std::endl;
                throw std::runtime_error("Error in test");
            }
        }
    }
    {
        ++i;
        std::vector<int> vec = {9, 3};
        TPrefixArray array(vec);
        int j = 0;
        {
            ++j;
            int start = 0;
            int end = 1;
            int computedSum = array.CalcSum(start, end);
            int realSum = 9;
            if (realSum != computedSum) {
                std::cerr << "error in test " << i << " case " << j << "; expected " << realSum << " got " << computedSum << std::endl;
                std::cerr << "start: " << start << "; end: " << end << "; vec: " << ToString(vec) << std::endl;
                throw std::runtime_error("Error in test");
            }
        }
    }
    {
        ++i;
        std::vector<int> vec = {3, 0, 9};
        TPrefixArray array(vec);
        int j = 0;
        {
            ++j;
            int start = 2;
            int end = 3;
            int computedSum = array.CalcSum(start, end);
            int realSum = 9;
            if (realSum != computedSum) {
                std::cerr << "error in test " << i << " case " << j << "; expected " << realSum << " got " << computedSum << std::endl;
                std::cerr << "start: " << start << "; end: " << end << "; vec: " << ToString(vec) << std::endl;
                throw std::runtime_error("Error in test");
            }
        }
    }
    {
        ++i;
        std::vector<int> vec = {3, 0, 0, 3};
        TPrefixArray array(vec);
        int j = 0;
        {
            ++j;
            int start = 1;
            int end = 3;
            int computedSum = array.CalcSum(start, end);
            int realSum = 0;
            if (realSum != computedSum) {
                std::cerr << "error in test " << i << " case " << j << "; expected " << realSum << " got " << computedSum << std::endl;
                std::cerr << "start: " << start << "; end: " << end << "; vec: " << ToString(vec) << std::endl;
                throw std::runtime_error("Error in test");
            }
        }
    }
    std::cout << "Starting brute testing!" << std::endl;
    {
        // brute force testing
        for (size_t j = 0; j < 100; ++j) {
            size_t size = rand() % 4 + 1;
            std::vector<int> vec = GenerateVector(size, /* max = */ 10);
            TPrefixArray array(vec);
            for (size_t k = 0; k < 100; ++k) {
                size_t start = 0;
                size_t end = 1;
                if (size != 0) {
                    size_t start = rand() % size;
                    size_t end = rand() % size + 1;
                    if (start > end) {
                        std::swap(start, end);
                    }
                    if (end == start) {
                        end += 1;
                    }
                }
                int expected = NaiveCalcSum(vec, start, end);
                int computed = array.CalcSum(start, end);
                if (expected != computed) {
                    std::cerr << "Error! Expected sum " << expected << "; computed " << computed << "; start: " << start << "; end: " << end << " vec: " << ToString(vec) << std::endl;
                    throw std::runtime_error("");
                }
                if (k == 50) {
                    std::cout << "expected: " << expected << "; computed: " << computed << "; test case #" << i << ":" << k << std::endl;
                }
            }
        }
    }
    std::cerr << "All success!" << std::endl;
    return 0;
}

static constexpr int MOD = 1000000007;

size_t GetNext(size_t x0) {
    return (11173 * x0 + 1) % MOD;
}

int main() {
    size_t N;
    std::cin >> N;
    std::vector<int> vec;
    vec.reserve(N);
    for (size_t i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        vec.push_back(x);
    }
    size_t Q;
    std::cin >> Q;
    size_t x0;
    std::cin >> x0;
    //std::cout << "x: " << x0 << std::endl;
    TPrefixArray array(vec);
    int resultSum;
    for (size_t q = 0; q < Q; ++q) {
        size_t x1 = GetNext(x0);
        //std::cout << "x: " << x1 << std::endl;
        size_t l = std::min(x0 % N, x1 % N);
        size_t r = std::max(x0 % N, x1 % N) + 1;
        //std::cout << "l: " << l << "; r: " << r << std::endl;
        long long result = array.CalcSum(l, r);
        //std::cout << "result: " << result << std::endl;
        resultSum += (result % MOD);
        resultSum %= MOD;
        x0 = GetNext(x1);
        //std::cout << "x: " << x0 << std::endl;
    }
    std::cout << resultSum << std::endl;
}