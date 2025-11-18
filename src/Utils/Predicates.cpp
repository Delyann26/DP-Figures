#include "Predicates.h"
#include <cmath>
#include <limits>


bool isValidSide(double x) {
	return std::isfinite(x) && x > 0;
}

bool willAddOverflow(double x, double y) {
    const double max = std::numeric_limits<double>::max();
    if (x == max && y > 0) {
        return true;
    }
    return x > max - y; //x+y > max
}

bool willMulOverflow(double x, double y) {
    const double max = std::numeric_limits<double>::max();
    if (y == 0) {
        return false;
    }
    return x > max / y; //xy > max
}
