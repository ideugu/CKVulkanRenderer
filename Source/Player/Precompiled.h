#pragma once

#if defined(PLATFORM_WINDOWS)
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#include <windows.h>
	#include <tchar.h>
	#define PLATFORM_MAIN()	int main()
//	#define PLATFORM_MAIN()	int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#else
	#define PLATFORM_MAIN()	int main()

#endif

#include "MathHeaders.h"
#include "EngineHeaders.h"
#include "RendererHeaders.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <array>
#include <optional>
#include <set>

using namespace CK;

