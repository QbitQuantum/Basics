#include <iostream>
#include <type_traits>
#include <string>

template <typename T>
T functions() {

	std::string s = "1T";
	int i = 1;
	bool b = false;

	if (typeid(std::string) == typeid(T)) {
		return s;
	}
	if (typeid(int) == typeid(T)) {
		return i;
	}
	if (typeid(bool) == typeid(T)) {
		return b;
	}
	return T();
};

int main() {
	std::string a = functions<decltype(a)>();
	std::cout << a;
}
