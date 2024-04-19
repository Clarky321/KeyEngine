#pragma once

#include <vector>
#include <initializer_list>

namespace KeyEngine {

	enum class ShaderDataType // Перечисление типов данных шейдера
	{
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
	};

	struct BufferElement // Структура, представляющая элемент буфера
	{
		ShaderDataType type;		// Тип данных элемента
		uint32_t component_type;	// Тип компонента
		size_t components_count;	// Количество компонентов
		size_t size;				// Размер элемента
		size_t offset;				// Смещение элемента

		BufferElement(const ShaderDataType type); // Конструктор с одним аргументом
	};

	class BufferLayout // Класс, представляющий макет буфера
	{

	public:

		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_elements(std::move(elements))
		{
			size_t offset = 0;
			m_stride = 0;

			for (auto& element : m_elements )
			{
				element.offset = offset;
				offset += element.size;
				m_stride += element.size;
			}
		}

		const std::vector<BufferElement>& get_elements() const { return m_elements; }
		size_t get_stride() const { return m_stride; }

	private:

		std::vector<BufferElement> m_elements;
		size_t m_stride = 0;
	};

	class VertexBuffer {

	public:

		enum class EUsage
		{
			Static,
			Dynamic,
			Stream
		};

		VertexBuffer(const void* data, const size_t size, BufferLayout buffer_layout, const EUsage usage = VertexBuffer::EUsage::Static);

		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;
		VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;
		VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;

		void bind() const;
		static void unbuid();

		const BufferLayout& get_layout() const { return m_buffer_layout; }

	private:
		unsigned int m_id = 0;
		BufferLayout m_buffer_layout;
	};
}