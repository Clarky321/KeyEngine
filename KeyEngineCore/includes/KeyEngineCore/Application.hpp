// Защита от множественного включения заголовочного файла
#pragma once

// Включение заголовочного файла для событий из вашего движка
#include "KeyEngineCore\Event.hpp"

// Включение заголовочного файла для умных указателей
#include <memory>

// Объявление класса Application в пространстве имен KeyEngine
namespace KeyEngine {

	// Класс представляет базовое приложение для использования в движке
	class Application
	{
	public:

		// Конструктор по умолчанию
		Application();
		// Виртуальный деструктор
		virtual ~Application();

		// Запрет на копирования и перемещения
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator = (const Application&) = delete;
		Application& operator = (Application&&) = delete;

		// Виртуальный метод для инициализации и запуска приложения
		virtual int start(unsigned int window_width, unsigned int window_height, const char* title);

		// Виртуальный метод для обновления состояния приложения в каждом кадре
		virtual void on_update() {}

	private:
		std::unique_ptr<class Window> m_pWindow; // Уникальный указатель на окно приложения

		EventDispatcher m_event_dispatcher; // Диспетчер событий
		bool m_bCloseWindow = false; // Флаг для закрытия окна
	};
}