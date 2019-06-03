cmake_minimum_required(VERSION 3.6.0 FATAL_ERROR)
project(opengl_basic)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
	src/main.cpp)

set(INCLUDE_DIRS include)

list(APPEND LIBRARIES glfw)
list(APPEND LIBRARIES GLEW)
list(APPEND LIBRARIES GL)
#list(APPEND LIBRARIES glm)

add_executable(${PROJECT_NAME}
	${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
	${LIBRARIES})
