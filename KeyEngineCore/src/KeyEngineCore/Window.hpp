// Защита от множественного включения заголовочного файла
#pragma once

#include "KeyEngineCore\Event.hpp"

#include <string>
#include <functional>

struct GLFWwindow;

// Объявление класса Application в пространстве имен KeyEngine
namespace KeyEngine {

	// Класс представляет базовое приложение для использования в движке
	class Window
	{
	public:

		using EventCallbackFn = std::function<void(BaseEvent&)>;

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

		unsigned int get_width() const { return m_data.width; }
		unsigned int get_height() const { return m_data.height; }

		void set_event_callback(const EventCallbackFn& callback)
		{
			m_data.eventCallbackFn = callback;
		}

	private:

		struct WindowData
		{
			std::string title;
			unsigned int width;
			unsigned int height;

			EventCallbackFn eventCallbackFn;
		};

		int init();
		void shutdown();

		GLFWwindow* m_pWindow = nullptr;

		WindowData m_data;
	};

}