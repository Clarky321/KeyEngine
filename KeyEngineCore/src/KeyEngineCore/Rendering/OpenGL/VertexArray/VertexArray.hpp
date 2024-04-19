// Защита от множественного включения заголовочного файла
#pragma once

#include "KeyEngineCore\Rendering\OpenGL\VertexBuffer\VertexBuffer.hpp"
#include "KeyEngineCore\Rendering\OpenGL\IndexBuffer\IndexBuffer.hpp"

namespace KeyEngine {

	class VertexArray {

	public:
		VertexArray();													// Конструктор по умолчанию
		~VertexArray();													// Деструктор

		VertexArray(const VertexArray&) = delete;						// Запрещено копирование объектов класса
		VertexArray& operator=(const VertexArray&) = delete;			// Запрещено присваивание объектов класса
		VertexArray& operator=(VertexArray&& vertex_buffer) noexcept;	// Перемещающее присваивание объектов класса
		VertexArray(VertexArray&& vertex_buffer) noexcept;				// Перемещающий конструктор

		void add_vertex_buffer(const VertexBuffer& vertex_buffer);		// Метод для добавления буфера вершин
		void set_index_buffer(const IndexBuffer& index_buffer);
		void bind() const;												// Метод для привязки массива вершин
		static void unbind();											// Статический метод для отвязки массива вершин
		size_t get_indices_count() const{ return m_indices_count; }

	private:
		unsigned int m_id = 0;											// Идентификатор (ID) массива вершин
		unsigned int m_elements_count = 0;								// Количество элементов в массиве вершин
		size_t m_indices_count = 0;
	};
}