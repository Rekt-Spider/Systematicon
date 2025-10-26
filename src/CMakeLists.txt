cmake_minimum_required(VERSION 3.16)
project(Systematicon)
# 2. Define the library target
add_library(HandlerLib SimulationHandler.cpp)

# 3. Add usage requirements to the library
target_include_directories(HandlerLib PUBLIC
  ${PROJECT_SOURCE_DIR}
)
target_compile_features(HandlerLib PUBLIC cxx_std_20)

# 4. Define the executable target
add_executable(SimulationHandler main.cpp)

# 5. Add usage requirements to the executable
target_compile_features(SimulationHandler PUBLIC cxx_std_20)

# 6. Link the library to the executable
target_link_libraries(SimulationHandler HandlerLib)