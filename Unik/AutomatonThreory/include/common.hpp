
#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <iostream>
#include <cstdlib>

__attribute__((__cold__, __noreturn__))
static inline void panic(const std::string &s)
{
	std::cerr << "PANIC: " << s << std::endl;
	std::abort();
}

static inline unsigned int powerof2(unsigned int x)
{
	return !(x & (x - 1));
}

#endif /* COMMON_HPP */

