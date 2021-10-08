#include <iostream>
#include <vector>

using i64 = int64_t;

/*
    (a, b) = x1x2 + y1y2 = |a||b|cos_alpha
    [a, b] = x1y2 - x2y1 = |a||b|sin_alpha
*/

/*
    todo:
    [ ] test #4 fails
        [ ] i64 overflow?
*/

i64 Dot(i64 x1, i64 y1, i64 x2, i64 y2) {
    //std::cout << "Dot: " << x1 * x2 + y1 * y2 << std::endl;
    return x1 * x2 + y1 * y2;
}

i64 Dot2(i64 x1, i64 y1, i64 x2, i64 y2) {
    //std::cout << "Dot2: " << x1 * y2 - x2 * y1 << std::endl;
    return x1 * y2 - x2 * y1;
}

int main() {
    i64 x1, y1, x2, y2, x3, y3;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    std::vector<i64> vec = {x1, y1, x2, y2, x3, y3};
    for (i64 i : vec) {
        if (i > 1e10) {
            throw std::runtime_error("");
        }
    }
    // find right angle
    i64 dot1 = Dot(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
    i64 dot2 = Dot(x2 - x3, y2 - y3, x1 - y3, y1 - y3);
    if (dot1 == 0 && dot2 == 0) {
        throw std::runtime_error("");
    }
    if (dot1 == 0) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    } else if (dot2 == 0) {
        std::swap(x3, x2);
        std::swap(y3, y2);
    }
    // x2, y2 is now the base of right angle
    i64 x = x1 + x3 - x2;
    i64 y = y1 + y3 - y2;
    std::cout << x << " " << y << std::endl;
    // std::vector<i64> vec2(1e6);
}