#include <iostream>
#include <tuple>


template<typename... Args>
void variadic_function(Args... args) {
    // Создаем кортеж из аргументов
    auto t = std::make_tuple(args...);
    // Печатаем кортеж
    std::apply([](auto&&... args) { ((std::cout << args << ' '), ...); std::cout << '\n'; }, t);
}



int main() {

    variadic_function(1, 2.5, "Hello");
    return 0;
}