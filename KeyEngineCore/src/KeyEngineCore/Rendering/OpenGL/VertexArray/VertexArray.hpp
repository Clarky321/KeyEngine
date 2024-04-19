// Защита от множественного включения заголовочного файла
#pragma once

#include "KeyEngineCore\Rendering\OpenGL\VertexBuffer\VertexBuffer.hpp"

namespace KeyEngine {

	class VertexArray {

	public:
		VertexArray();													// Конструктор по умолчанию
		~VertexArray();													// Деструктор

		VertexArray(const VertexArray&) = delete;						// Запрещено копирование объектов класса
		VertexArray& operator=(const VertexArray&) = delete;			// Запрещено присваивание объектов класса
		VertexArray& operator=(VertexArray&& vertex_buffer) noexcept;	// Перемещающее присваивание объектов класса
		VertexArray(VertexArray&& vertex_buffer) noexcept;				// Перемещающий конструктор

		void add_buffer(const VertexBuffer& vertex_buffer);				// Метод для добавления буфера вершин
		void bind() const;												// Метод для привязки массива вершин
		static void unbind();											// Статический метод для отвязки массива вершин

	private:
		unsigned int m_id = 0;											// Идентификатор (ID) массива вершин
		unsigned int m_elements_count = 0;								// Количество элементов в массиве вершин
	};
}