# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.12)

# Определение названия проекта KeyEngineCore
set(ENGINE_PROJECT_NAME KeyEngineCore)

set(ENGINE_PUBLIC_INCLUDES
	includes/KeyEngineCore/Application.hpp
	includes/KeyEngineCore/Log.hpp
)

set(ENGINE_PRIVATE_SOURCES
	src/KeyEngineCore/Application.cpp
)

# Создание статической библиотеки с названием KeyEngineCore
add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)

# Добавление пути к заголовочным файлам KeyEngineCore для внешних пользователей
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)

# Установка стандарта C++ для компиляции
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

# Добавление подмодуля GLFW и его сборка
add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
# Линковка с библиотекой GLFW
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

# Добавление подмодуля SPDLOG и его сборка
add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
# Линковка с библиотекой SPDLOG
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)