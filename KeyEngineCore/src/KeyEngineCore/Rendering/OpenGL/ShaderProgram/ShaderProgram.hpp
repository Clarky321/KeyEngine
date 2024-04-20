// Защита от множественного включения заголовочного файла
#pragma once

#include <glm\mat4x4.hpp>

namespace KeyEngine {

	class ShaderProgram
	{
	public:
		// Конструктор класса ShaderProgram, принимающий исходные коды вершинного и фрагментного шейдеров
		ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);

		// Конструктор перемещения
		ShaderProgram(ShaderProgram&&);

		// Оператор перемещения
		ShaderProgram& operator=(ShaderProgram&&);

		// Деструктор класса ShaderProgram
		~ShaderProgram();

		// Запрещаем создание объектов по умолчанию, копирование и присваивание
		ShaderProgram() = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		// Метод для привязки шейдерной программы
		void bind() const;

		// Статический метод для отвязки шейдерной программы
		static void unbind();

		// Метод для проверки, была ли программа успешно скомпилирована
		bool isCompiled() const { return m_is_compiled; }

		void setMatrix4(const char* name, const glm::mat4& matrix) const;

	private:
		// Переменная для хранения информации о том, была ли программа скомпилирована
		bool m_is_compiled = false;

		// Идентификатор шейдерной программы
		unsigned int m_id = 0;
	};
}