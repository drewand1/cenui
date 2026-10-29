#include "cenui/err.h"

void rtWarn(const std::string& msg) {
	std::cerr << "\033[33m[CENUI][Runtime warning]: " << msg << "\033[0m" << std::endl;
}