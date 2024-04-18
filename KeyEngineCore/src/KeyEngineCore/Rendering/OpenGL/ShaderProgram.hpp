// Защита от множественного включения заголовочного файла
#pragma once

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
		bool isCompiled() const { return m_isCompiled; }

	private:
		// Переменная для хранения информации о том, была ли программа скомпилирована
		bool m_isCompiled = false;

		// Идентификатор шейдерной программы
		unsigned int m_id = 0;
	};
}