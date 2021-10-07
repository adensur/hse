#include <iostream>

using i64 = int64_t;

int main() {
    i64 x1, y1, x2, y2;
    double A, B, C;
    std::cin >> x1 >> y1 >> x2 >> y2;
    A = y2 - y1;
    B = x1 - x2;
    C = x2 * y1 - x1 * y2;
    std::cout << A << " " << B << " " << C << std::endl;
}