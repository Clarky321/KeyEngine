# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.12)

# Определение названия проекта KeyEngineEditor
set(EDITOR_PROJECT_NAME KeyEngineEditor)

# Создание исполняемого файла с названием KeyEngineEditor и указание его исходного файла
add_executable(${EDITOR_PROJECT_NAME}
	src/main.cpp
)

# Линковка исполняемого файла с библиотекой KeyEngineCore
target_link_libraries(${EDITOR_PROJECT_NAME} KeyEngineCore)

# Установка стандарта C++ для компиляции
target_compile_features(${EDITOR_PROJECT_NAME} PUBLIC cxx_std_17)

# Установка каталога для вывода исполняемого файла
set_target_properties(${EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)