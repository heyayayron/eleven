#ifndef ELEVEN_ELPCH_H
#define ELEVEN_ELPCH_H

#define EL_PLATFORM_WINDOWS

#ifdef EL_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <array>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <fstream>

#include <intsafe.h>
#include <exception>
#include <cstdint>

#define GLFW_INCLUDE_NONE
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#endif //ELEVEN_ELPCH_H
