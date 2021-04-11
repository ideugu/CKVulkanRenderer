cmake_minimum_required(VERSION 3.1)

project(VulkanPlayer)

################################################################################
# Vulkan Package
################################################################################
IF(UNIX AND NOT APPLE)
	set(LINUX TRUE)
ENDIF()

IF(WIN32)
	IF (NOT Vulkan_FOUND)
		find_library(Vulkan_LIBRARY NAMES vulkan-1 vulkan PATHS ${PROJECT_SOURCE_DIR}/ThirdParty/vulkan/Lib)
		IF (Vulkan_LIBRARY)
			set(Vulkan_FOUND ON)
			MESSAGE("Using bundled Vulkan library version")
		ENDIF()
	ENDIF()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_WIN32_KHR")
ELSEIF(LINUX)
	IF (NOT Vulkan_FOUND)
		find_library(Vulkan_LIBRARY NAMES vulkan HINTS "$ENV{VULKAN_SDK}/lib" "${PROJECT_SOURCE_DIR}/ThirdParty/vulkan/Lib" REQUIRED)
		IF (Vulkan_LIBRARY)
			set(Vulkan_FOUND ON)
			MESSAGE("Using bundled Vulkan library version")
		ENDIF()
	ENDIF()
	find_package(Threads REQUIRED)
ELSEIF(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_MACOS_MVK -DVK_EXAMPLE_XCODE_GENERATED")
	# Todo : android?
ENDIF(WIN32)

IF (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
	message(STATUS ${Vulkan_LIBRARY})
ENDIF()

find_library(Glfw_LIBRARY NAMES glfw3 PATHS ${PROJECT_SOURCE_DIR}/ThirdParty/glfw/lib)

################################################################################
# Source files
################################################################################
file(GLOB COMMON_SOURCE_FILES
	${PROJECT_SOURCE_DIR}/Private/*.cpp
	${PROJECT_SOURCE_DIR}/*.cpp
	${PROJECT_SOURCE_DIR}/*.h
	)
		
set(ALL_FILES
    ${COMMON_SOURCE_FILES}
    )
	   

foreach(FILE ${ALL_FILES})
    # make rel path
	file(RELATIVE_PATH REL_PATH "${PROJECT_SOURCE_DIR}" "${FILE}")

    # get the base path
    get_filename_component(BASE_PATH "${REL_PATH}" PATH)

    # changes /'s to \\'s
    string(REPLACE "/" "\\" GROUP "${BASE_PATH}")

    source_group("${GROUP}" FILES "${FILE}")
endforeach()


################################################################################
# Include directory
################################################################################	
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/ThirdParty/vulkan/Include
    ${PROJECT_SOURCE_DIR}/ThirdParty/glfw/include
    ${RUNTIME_MODULE_DIR}/Math/Public
    ${RUNTIME_MODULE_DIR}/Engine/Public
    ${RUNTIME_MODULE_DIR}/Renderer/Public
	)


################################################################################
# Precompiled Headers
################################################################################
set(ARG_PCH_HEADER Precompiled.h)
set(ARG_PCH_SOURCE Precompiled.cpp)
foreach (FILE ${ALL_FILES})
  file(RELATIVE_PATH REL_PATH "${PROJECT_SOURCE_DIR}" "${FILE}")
  if (REL_PATH MATCHES ".*\\.(c|cpp)$")
	if (REL_PATH STREQUAL ${ARG_PCH_SOURCE})
	  set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/Yc\"${ARG_PCH_HEADER}\"")
	else()
	  set_source_files_properties(${FILE} PROPERTIES COMPILE_FLAGS "/Yu\"${ARG_PCH_HEADER}\"")
	endif()
  endif()
endforeach(FILE)

IF(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
ELSEIF(APPLE)
	if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc -ObjC++")
	ELSE()
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc -xobjective-c++")
	ENDIF()
ENDIF(MSVC)

################################################################################
# Excutable Output Setting
################################################################################
IF(WIN32)
	add_executable(${PROJECT_NAME} ${ALL_FILES})
ELSE(WIN32)
	add_executable(${PROJECT_NAME} ${ALL_FILES})
ENDIF(WIN32)

set_target_properties(${PROJECT_NAME} PROPERTIES
	PREFIX ""
	OUTPUT_NAME ${PROJECT_NAME}
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/${PLATFORM_FOLDER}/Binary
	VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Resource 
)
	
################################################################################
# Library Setting
################################################################################
IF(WIN32)
IF(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt")
ENDIF(MSVC)
ENDIF(WIN32)

IF(WIN32)
	target_link_libraries(${PROJECT_NAME} MathModule EngineModule RendererModule ${Vulkan_LIBRARY} ${Glfw_LIBRARY})
ELSEIF(APPLE)
	target_link_libraries(${PROJECT_NAME} MathModule EngineModule RendererModule ${Vulkan_LIBRARY} ${Glfw_LIBRARY} "-framework AppKit" "-framework QuartzCore")
ELSE(WIN32)
	target_link_libraries(${PROJECT_NAME} MathModule EngineModule RendererModule ${Vulkan_LIBRARY} ${Glfw_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
ENDIF(WIN32)
