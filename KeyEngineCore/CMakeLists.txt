# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.12)

# Определение названия проекта KeyEngineCore
set(ENGINE_PROJECT_NAME KeyEngineCore)

set(ENGINE_PUBLIC_INCLUDES
	includes/KeyEngineCore/Application.hpp
	includes/KeyEngineCore/Log.hpp
	includes/KeyEngineCore/Event.hpp
)

set(ENGINE_PRIVATE_INCLUDES
	src/KeyEngineCore/Window/Window.hpp
	src/KeyEngineCore/Rendering/OpenGL/ShaderProgram/ShaderProgram.hpp
	src/KeyEngineCore/Rendering/OpenGL/VertexBuffer/VertexBuffer.hpp
	src/KeyEngineCore/Rendering/OpenGL/VertexArray/VertexArray.hpp
	src/KeyEngineCore/Rendering/OpenGL/IndexBuffer/IndexBuffer.hpp
)

set(ENGINE_PRIVATE_SOURCES
	src/KeyEngineCore/Application.cpp
	src/KeyEngineCore/Window/Window.cpp
	src/KeyEngineCore/Rendering/OpenGL/ShaderProgram/ShaderProgram.cpp
	src/KeyEngineCore/Rendering/OpenGL/VertexBuffer/VertexBuffer.cpp
	src/KeyEngineCore/Rendering/OpenGL/VertexArray/VertexArray.cpp
	src/KeyEngineCore/Rendering/OpenGL/IndexBuffer/IndexBuffer.cpp
)

set(ENGINE_ALL_SOURCE
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)

# Создание статической библиотеки с названием KeyEngineCore
add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_ALL_SOURCE}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${ENGINE_ALL_SOURCE}
)

# Добавление пути к заголовочным файлам KeyEngineCore для внешних пользователей
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)

target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)

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

# Добавление подмодуля GLAD и его сборка
add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
# Линковка с библиотекой GLAD
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)



set(IMGUI_INCLUDES
	../external/imgui/imgui.h
	../external/imgui/backends/imgui_impl_glfw.h
	../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES
	../external/imgui/imgui.cpp
	../external/imgui/backends/imgui_impl_glfw.cpp
	../external/imgui/backends/imgui_impl_opengl3.cpp
	
	../external/imgui/imgui_draw.cpp
	../external/imgui/imgui_widgets.cpp
	../external/imgui/imgui_tables.cpp
	
	../external/imgui/imgui_demo.cpp
)

add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)
target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)