#include <iomanip>
#include <iostream>

using i64 = int64_t;

void Normalize(i64& A, i64& B, i64& C) {
    if (A < 0) {
        A *= -1;
        B *= -1;
        C *= -1;
        return;
    }
    if (A > 0) {
        return;
    }
    // A == 0
    if (B < 0) {
        B *= -1;
        C *= -1;
    }
}

int main() {
    i64 x1, y1, x2, y2, x3, y3, x4, y4;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    // case1 - parallel
    i64 A1 = y1 - y2;
    i64 A2 = y3 - y4;
    i64 B1 = x2 - x1;
    i64 B2 = x4 - x3;
    i64 C1 = x1 * y2 - x2 * y1;
    i64 C2 = x3 * y4 - x4 * y3;
    Normalize(A1, B1, C1);
    Normalize(A2, B2, C2);
    if ((y1 - y2) * (x4 - x3) == (y3 - y4) * (x2 - x1)) {
        // parallel or equal lines
        if (C1 != C2) {
            // parallel, not equal
            std::cout << "0" << std::endl;
            return 0;
        }
        // equal
        std::cout << "2" << std::endl;
        return 0;
    }
    // not parallel
    // find intersection
    double y = static_cast<double>(A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);
    double x;
    if (A1 != 0) {
        x = (static_cast<double>(-C1) - B1 * y) / A1;
    } else {
        x = (static_cast<double>(-C2) - B2 * y) / A2;
    }
    std::cout << "1 " << std::setprecision(2) << std::fixed << x << " " << y << std::endl;
    return 0;
}   