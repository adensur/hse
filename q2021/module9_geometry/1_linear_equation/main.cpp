#include <iostream>

using i64 = int64_t;

int main() {
    i64 x1, y1, x2, y2;
    double A, B, C;
    std::cin >> x1 >> y1 >> x2 >> y2;
    if (y1 == y2) {
        A = 0.0;
        B = -1.0;
        C = y1;
    } else {
        A = 1.0;
        B = static_cast<double>(x1 - x2) / (y2 - y1);
        C = -x1 - B * y1;
    }
    std::cout << A << " " << B << " " << C << std::endl;
}