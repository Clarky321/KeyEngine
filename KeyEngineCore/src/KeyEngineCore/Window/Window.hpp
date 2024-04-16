// Защита от множественного включения заголовочного файла
#pragma once

// Включение заголовочного файла для событий из вашего движка
#include "KeyEngineCore\Event.hpp"

// Включение необходимых заголовочных файлов из стандартной библиотеки
#include <string>
#include <functional>

// Структура вызова из GLFWwindow
struct GLFWwindow;

// Объявление класса Application в пространстве имен KeyEngine
namespace KeyEngine {

	// Класс представляет базовое приложение для использования в движке
	class Window
	{
	public:
		// Определение типа функции обратного вызова для событий окна
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

		// Методы доступа к ширине и высоте окна
		unsigned int get_width() const { return m_data.width; }
		unsigned int get_height() const { return m_data.height; }

		// Метод для установки обратного вызова событий окна
		void set_event_callback(const EventCallbackFn& callback) { m_data.eventCallbackFn = callback; }

	private:
		// Внутренняя структура данных окна
		struct WindowData
		{
			std::string title;
			unsigned int width;
			unsigned int height;

			EventCallbackFn eventCallbackFn;
		};

		// Методы инициализации и завершения работы с окном
		int init();
		void shutdown();

		GLFWwindow* m_pWindow = nullptr; // Указатель на объект окна GLFW

		WindowData m_data; // Данные окна
		float m_background_color[4] = { 0.f, 0.f, 0.f, 0.f };
	};
}