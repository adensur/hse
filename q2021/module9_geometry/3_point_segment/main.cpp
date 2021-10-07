#include <iostream>

using i64 = int64_t;

int main() {
    i64 x0, y0, x1, y1, x2, y2;
    std::cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
    i64 eqResult = x0 * (y2 - y1) + y0 * (x1 - x2) + (x2 * y1 - x1 * y2);
    if (eqResult != 0) {
        std::cout << "NO" << std::endl;
        return 0;
    }
    if (x1 == x2) {
        // vertical line
        if (y0 == y1) {
            std::cout << "YES" << std::endl;
            return 0;
        }
        if (y2 < y1) {
            std::swap(y1, y2);
        }
        if (y0 >= y1 && y0 <= y2) {
            std::cout << "YES" << std::endl;
            return 0;
        } else {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }
    // not a vertical line
    if (x1 == x0) {
        std::cout << "YES" << std::endl;
        return 0;
    }
    if (x2 < x1) {
        std::swap(x1, x2);
    }
    if (x0 >= x1 && x0 <= x2) {
        std::cout << "YES" << std::endl;
        return 0;
    }
    std::cout << "NO" << std::endl;
    return 0;
}