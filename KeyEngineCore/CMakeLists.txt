# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.12)

# Определение названия проекта KeyEngineCore
set(ENGINE_PROJECT_NAME KeyEngineCore)

# Создание статической библиотеки с названием KeyEngineCore
add_library(${ENGINE_PROJECT_NAME} STATIC
	src/KeyEngineCore/Utils/test.cpp
	includes/KeyEngineCore/Utils/test.hpp
)

# Добавление пути к заголовочным файлам KeyEngineCore для внешних пользователей
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)

# Установка стандарта C++ для компиляции
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

# Добавление подмодуля GLFW и его сборка
add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
# Линковка с библиотекой GLFW
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)