#include <iostream>

using i64 = int64_t;

/*
    [a, b] = x1y2 - x2y1 = |a||b|sin_alpha
*/

i64 Dot(i64 x1, i64 y1, i64 x2, i64 y2) {
    return x1 * y2 - x2 * y1;
}

int main() {
    i64 x0, y0, x1, y1, x2, y2;
    std::cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;
    i64 dot = Dot(x2 - x1, y2 - y1, x0 - x1, y0 - y1);
    //std::cout << dot << std::endl;
    if (dot > 0) {
        std::cout << "LEFT" << std::endl;
    } else if (dot == 0) {
        std::cout << "BOTH" << std::endl;
    } else {
        std::cout << "RIGHT" << std::endl;
    }
}