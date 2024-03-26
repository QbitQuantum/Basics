#include <iostream>
#include <type_traits>

template <typename T, std::enable_if_t<std::is_same_v<T, std::string>, bool> = true>
T functions() {
    return "2T";
}

template <typename T, std::enable_if_t<std::is_same_v<T, int>, bool> = true>
T functions() {
    return 2;
}

template <typename T, std::enable_if_t<std::is_same_v<T, bool>, bool> = true>
T functions() {
    return true;
}

int main() {
    std::string b = functions<decltype(b)>();
    std::cout << b;
    return 0;
}
