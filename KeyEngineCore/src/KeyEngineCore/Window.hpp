// Защита от множественного включения заголовочного файла
#pragma once

#include <string>

struct GLFWwindow;

// Объявление класса Application в пространстве имен KeyEngine
namespace KeyEngine {

	// Класс представляет базовое приложение для использования в движке
	class Window
	{
	public:

		// Конструктор по умолчанию
		Window(std::string title, const unsigned int width, const unsigned int height);

		// деструктор
		~Window();

		// Запрет копирования и перемещения
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator = (const Window&) = delete;
		Window& operator = (Window&&) = delete;

		// метод для обновления состояния приложения в каждом кадре
		void on_update();

		unsigned int get_width() const { return m_width; }
		unsigned int get_height() const { return m_height; }

	private:

		int init();
		void shutdown();

		GLFWwindow* m_pWindow;

		std::string m_title;
		unsigned int m_width;
		unsigned int m_height;
	};

}