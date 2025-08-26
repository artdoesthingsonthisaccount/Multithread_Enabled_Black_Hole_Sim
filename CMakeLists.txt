# cmake_minimum_required(VERSION 3.31.6)
# project(BH_sim CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(PkgConfig REQUIRED)
# find_package(glfw3 REQUIRED)
# pkg_check_modules(GLEW REQUIRED glew)
# find_package(glm QUIET)

# add_executable(${PROJECT_NAME} src/main.cpp)
# target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})

# target_link_directories(${PROJECT_NAME}
#     PRIVATE
#         glfw
#         ${GLEW_LIBRARIES}
#         OpenGL::GL
# )

# if (TARGET glm::glm)
#     target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
# else ()
#     target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
# endif()


# add_subdirectory(./lib)

cmake_minimum_required(VERSION 3.16)
project(BH_sim CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)
pkg_check_modules(GLEW  REQUIRED glew)
find_package(OpenGL REQUIRED)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLFW3_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLFW3_LIBRARIES}
    ${GLEW_LIBRARIES}
    OpenGL::GL
    Eigen3::Eigen
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${GLFW3_LIBRARY_DIRS}
    ${GLEW_LIBRARY_DIRS}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    ${GLFW3_CFLAGS_OTHER}
    ${GLEW_CFLAGS_OTHER}
)
target_link_options(${PROJECT_NAME} PRIVATE
    ${GLFW3_LDFLAGS_OTHER}
    ${GLEW_LDFLAGS_OTHER}
)
