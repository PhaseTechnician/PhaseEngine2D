#pragma once

#include <glad/glad.h>
#include <iostream>

#define DEBUG

inline void debugGLMessage(string mes) {
#ifdef DEBUG
	if (glGetError()) {
		std::cout << glGetError() << mes << std::endl;
	}
#endif // DEBUG
}