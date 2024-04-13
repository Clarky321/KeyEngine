# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.12)

# Определение названия проекта
set(PROJECT_NAME KeyEngine)

# Добавления поддиректории для модуля KeyEngineCore(ядро движка)
add_subdirectory(KeyEngineCore)

# Добавления поддиректории для модуля KeyEngineEditor
add_subdirectory(KeyEngineEditor)

# Установка KeyEngineEditor в качестве стартового проекта для Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT KeyEngineEditor)
