bool IsPrime(const int64_t& INPUT_NUM) {
    using std::sqrt;
    using std::floor;
    // We hard code in a few cases, then test in general
    if (INPUT_NUM < 2) {  // 0, 1 and negative are not prime
        return false;
    } else if (INPUT_NUM < 4) {  // 3 is prime
        return true;
    } else if (INPUT_NUM % 2 == 0) {  // even numbers are not prime
        return false;
    } else if (INPUT_NUM < 9) {  // 6, 8 has been removed above
        return true;
    } else if (INPUT_NUM % 3 == 0) {  // numbers divisible by 3 are not prime
        return false;
    } else {
        const double FLOOR_ROOT = floor(sqrt(INPUT_NUM));
        const int R = static_cast<int>(FLOOR_ROOT);
        int f = 5;

        while (f <= R) {
            if (INPUT_NUM % f == 0) {
                return false;
            } else if (INPUT_NUM % (f + 2) == 0) {
                return false;
            } else {
                f += 6;
            }
        }
        return true;
    }
}