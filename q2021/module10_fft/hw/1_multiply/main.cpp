#include <complex>
#include <iostream>
#include <numbers>
#include <sstream>
#include <vector>

using i64 = int64_t;

using TComplexNumber = std::complex<double>;

template <class T>
std::string ToString(const std::vector<T>& vec) {
    std::stringstream ss;
    for (const T& obj : vec) {
        ss << obj << " ";
    }
    return ss.str();
}

std::vector<TComplexNumber> Fft(const std::vector<TComplexNumber>& poly, bool invert = false) {
    i64 N = poly.size();
    if (N == 1) {
        return {poly[0]};
    }
    std::vector<TComplexNumber> poly1(N/2), poly2(N/2);
    for (i64 i = 0; i < poly.size(); i += 2) {
        poly1[i/2] = poly[i];
        poly2[i/2] = poly[i + 1];
    }
    std::vector<TComplexNumber> fft1 = Fft(poly1, invert);
    std::vector<TComplexNumber> fft2 = Fft(poly2, invert);
    std::vector<TComplexNumber> result;
    result.reserve(N);
    TComplexNumber w(1);
    double alpha;
    if (invert) {
        alpha = -2.0 * std::numbers::pi / N;
    } else {
        alpha = 2.0 * std::numbers::pi / N;
    }
    TComplexNumber wn(cos(alpha), sin(alpha));
    for (i64 i = 0; i < N; ++i) {
        TComplexNumber num = fft1[i % (N / 2)] + w * fft2[i % (N / 2)];
        if (invert) {
            num /= 2;
        }
        result.push_back(num);
        w *= wn;
        w %= MODULO;
    }
    return result;
}

std::vector<TComplexNumber> StringToComplexSequence(const std::string& number, i64 N) {
    std::vector<TComplexNumber> result(N, TComplexNumber(0));
    for (i64 i = 0; i < number.size(); ++i) {
        char ch = number[i];
        if (ch == '-') {
            continue;
        }
        result[number.size() - i - 1] = TComplexNumber(static_cast<double>(ch - '0'));
    }
    return result;
}

std::string Multiply(const std::string& number1, const std::string& number2) {
    i64 maxSize = std::max(number1.size(), number2.size());
    i64 N = pow(2, 1 + ceil(log2(maxSize)));
    //std::cerr << "N: " << N << std::endl;
    bool negative = false;
    if (number1[0] == '-') {
        negative = !negative;
    }
    if (number2[0] == '-') {
        negative = !negative;
    }
    std::vector<TComplexNumber> poly1 = StringToComplexSequence(number1, N);
    std::vector<TComplexNumber> poly2 = StringToComplexSequence(number2, N);
    std::vector<TComplexNumber> fft1 = Fft(poly1);
    std::vector<TComplexNumber> fft2 = Fft(poly2);
    std::vector<TComplexNumber> fft_product;
    fft_product.reserve(fft1.size());
    for (i64 i = 0; i < fft1.size(); ++i) {
        fft_product.push_back(fft1[i] * fft2[i]);
    }
    std::vector<TComplexNumber> ift = Fft(fft_product, /* invert = */ true);
    //std::cerr << "ift: " << ToString(ift) << std::endl;
    i64 remainder = 0;
    std::string result;
    result.reserve(N);
    i64 lastNonZeroIndex = 0;
    for (i64 i = 0; i < ift.size(); ++i) {
        i64 real = round(ift[i].real());
        real += remainder;
        result.push_back('0' + real % 10);
        remainder = real / 10;
        if (real > 0) {
            lastNonZeroIndex = i;
        }
    }
    result.resize(lastNonZeroIndex + 1);
    if (negative && ! (result == "0")) {
        result.push_back('-');
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::string number1, number2;
    std::cin >> number1 >> number2;
    std::string m = Multiply(number1, number2);
    std::cout << m << std::endl;
}