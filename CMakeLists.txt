# 使用现代 CMake 的最低版本建议
cmake_minimum_required(VERSION 3.20)

# 项目名称和语言
project(Pourwar CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- 查找依赖项 ---
find_package(SDL2 REQUIRED)

# --- 定义可执行文件 ---
# 将所有源文件添加到可执行文件中
add_executable(${PROJECT_NAME} WIN32 src/main.cpp)

# --- 链接依赖项 ---
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2)


# --- 组装输出文件夹 ---
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/static/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_SOURCE_DIR}/static/log.txt"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/log.txt"
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_SOURCE_DIR}/static/save.txt"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/save.txt"
    COMMENT "Copying assets and data files to output directory..."
)