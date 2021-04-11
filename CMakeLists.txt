##########################################################
## CMake Setting for VulkanRenderer 
##########################################################
cmake_minimum_required(VERSION 3.1)
if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
	message(STATUS "Using module to find Vulkan")
	find_package(Vulkan)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMakeDependentOption)
set(MAIN_PROJECT_NAME CKVulkanRenderer)

project(${MAIN_PROJECT_NAME})

set(RUNTIME_MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source/Runtime)

if(WIN32)
	set(PLATFORM_DEFINITION PLATFORM_WINDOWS)
	set(PLATFORM_FOLDER Windows)
endif()

################################################################################
# Sub projects
################################################################################

add_subdirectory(Source/Runtime/Math)
add_subdirectory(Source/Runtime/Engine)
add_subdirectory(Source/Runtime/Renderer)
add_subdirectory(Source/Player)

################################################################################
# Definitions
################################################################################
target_compile_definitions(VulkanPlayer PUBLIC ${PLATFORM_DEFINITION} ${PLATFORM_FOLDER})
target_compile_definitions(MathModule PUBLIC ${PLATFORM_DEFINITION} ${PLATFORM_FOLDER})
target_compile_definitions(EngineModule PUBLIC ${PLATFORM_DEFINITION} ${PLATFORM_FOLDER})
target_compile_definitions(RendererModule PUBLIC ${PLATFORM_DEFINITION} ${PLATFORM_FOLDER})

################################################################################
# Solution Setting
################################################################################
set(CMAKE_SUPPRESS_REGENERATION true)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT VulkanPlayer)

