#ifndef CENUI_ERR_H
#define CENUI_ERR_H

#include <iostream>
#include <string>

template <typename T>
void assertEx(T cond, const std::string& msg) {
	if (!cond) {
		std::cerr << "\033[31m[CENUI][Fatal error]: " << msg << "\033[0m" << std::endl;
		exit(-1);
	}
}

template  <typename T>
void assertWarn(T cond, const std::string& msg) {
	if (!cond) {
		std::cerr << "\033[33m[CENUI][Runtime warning]: " << msg << "\033[0m" << std::endl;
	}
}

void rtWarn(const std::string& msg);

#endif