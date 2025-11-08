# cmake_minimum_required(VERSION 3.16)
# project(Systematicon)
# # 2. Define the library target
# add_library(HandlerLib SimulationHandler.cpp)

# # 3. Add usage requirements to the library
# target_include_directories(HandlerLib PUBLIC
#   ${PROJECT_SOURCE_DIR}
# )
# target_compile_features(HandlerLib PUBLIC cxx_std_20)

# # 4. Define the executable target
# add_executable(SimulationHandler main.cpp)

# # 5. Add usage requirements to the executable
# target_compile_features(SimulationHandler PUBLIC cxx_std_20)

# # 6. Link the library to the executable
# target_link_libraries(SimulationHandler HandlerLib)

#Claude generated build instructions
cmake_minimum_required(VERSION 3.16)
project(Systematicon)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Add external libraries
add_library(GLAD STATIC ${PROJECT_SOURCE_DIR}/../libs/glad/glad.c)
target_include_directories(GLAD PUBLIC 
    ${PROJECT_SOURCE_DIR}/../libs
    ${PROJECT_SOURCE_DIR}/../libs/glad)

# Add ImGui library
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/../libs/imgui)
add_library(ImGui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${PROJECT_SOURCE_DIR}/../libs/backends/imgui_impl_glfw.cpp
    ${PROJECT_SOURCE_DIR}/../libs/backends/imgui_impl_opengl3.cpp
)
target_include_directories(ImGui PUBLIC 
    ${IMGUI_DIR}
    ${PROJECT_SOURCE_DIR}/../libs/backends
)

# Include GLM
include_directories(${PROJECT_SOURCE_DIR}/../libs/glm)

# Create library for core components
add_library(HandlerLib 
    SimulationHandler.cpp
    GUI.cpp
    ${PROJECT_SOURCE_DIR}/../include/Camera.cpp
    ${PROJECT_SOURCE_DIR}/../include/Shader.cpp
    ${PROJECT_SOURCE_DIR}/../include/Sphere.cpp
    ${PROJECT_SOURCE_DIR}/../include/Window.cpp
)

# Set include directories for HandlerLib
target_include_directories(HandlerLib PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/..
    ${PROJECT_SOURCE_DIR}/../include
    ${PROJECT_SOURCE_DIR}/../libs/glad
)

# Make HandlerLib depend on GLAD
target_link_libraries(HandlerLib
    PUBLIC GLAD
)

# Set C++20 standard for HandlerLib
target_compile_features(HandlerLib PUBLIC cxx_std_20)

# Define the executable
add_executable(Systematicon main.cpp)

# Link libraries to the executable
target_link_libraries(Systematicon 
    HandlerLib
    ImGui
    GLAD
    glfw
    OpenGL::GL
)

# Set C++20 standard for executable
target_compile_features(Systematicon PUBLIC cxx_std_20)
