
#include <iostream>
#include <type_traits>
#include <string>

template <typename T>
    typename std::conditional<std::is_same<T, std::string>::value, std::string,
    typename std::conditional<std::is_same<T, int>::value, int,
    typename std::conditional<std::is_same<T, bool>::value, bool, void>::type>::type>::type
    functions() {
    if constexpr (std::is_same<T, std::string>::value) {
        return "2T";
    }
    else if constexpr (std::is_same<T, int>::value) {
        return 2;
    }
    else if constexpr (std::is_same<T, bool>::value) {
        return false;
    }
    else {
        static_assert(std::is_same<T, void>::value, "Unsupported type");
    }
}

int main() {
    int b = functions<decltype(b)>();
    std::cout << b;
    return 0;
}



