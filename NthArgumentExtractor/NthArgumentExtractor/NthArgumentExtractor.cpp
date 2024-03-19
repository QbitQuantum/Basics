#include <iostream>
#include <tuple>
#include <typeinfo>

template<typename... Args>
void variadic_function(Args... args) {
    // Создаем кортеж из аргументов
    auto t = std::make_tuple(args...);
    // Печатаем кортеж
    std::apply([](auto&&... args) { ((std::cout << args << ' '), ...); std::cout << '\n'; }, t);
}


// Функция, которая принимает пакет параметров
template<typename... Args>
void print_args(Args... args) {
    // Создаем tuple из аргументов
    std::tuple<Args...> t(args...);

    // Выводим типы аргументов
    std::cout << "Types of arguments: ";
    std::apply([](auto&&... args) {((std::cout << typeid(args).name() << "\n"), ...);  }, t);
    std::cout << std::endl;

    // Выводим количество аргументов
    std::cout << "Number of arguments: " << sizeof...(Args) << std::endl;
}

#define NUM_ARGS(...) std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value
#define ARG_TYPE(i, ...) typename std::tuple_element<i, decltype(std::make_tuple(__VA_ARGS__))>::type


int main() {

    std::cout << NUM_ARGS(1, 2.0, 'a') << std::endl; // Выведет 3
    std::cout << std::is_same<ARG_TYPE(0, 1, 2.0, 'a'), int>::value << std::endl; // Выведет 1
    std::cout << std::is_same<ARG_TYPE(1, 1, 2.0, 'a'), double>::value << std::endl; // Выведет 1
    std::cout << std::is_same<ARG_TYPE(2, 1, 2.0, 'a'), char>::value << std::endl; // Выведет 1


    variadic_function(1, 2.5, "Hello");
    print_args(1, 2.5, "hello");
    return 0;
}