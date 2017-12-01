#include<cstdio>
#include "It.h"

void IT(const char* message) {
	std::printf(BLUE_TERM_COLOR);
	std::printf(ALLIGNED_GTEST_MESSAGE, message);
	std::printf(DEFAULT_TERM_COLOR);
}