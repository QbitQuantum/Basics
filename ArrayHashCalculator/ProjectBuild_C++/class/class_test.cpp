
#include "class_test.hpp"

bool class_base::check(std::string name) {
	return (this->name == name) ? !this->status : this->status;
}