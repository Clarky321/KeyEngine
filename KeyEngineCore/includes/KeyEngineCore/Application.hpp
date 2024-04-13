// Защита от множественного включения заголовочного файла
#pragma once

// Объявление класса Application в пространстве имен KeyEngine
namespace KeyEngine {

	// Класс представляет базовое приложение для использования в движке
	class Application
	{
		// Конструктор по умолчанию
		Application();

		// Виртуальный деструктор
		virtual ~Application();

		// Запрет копирования и перемещения
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator = (const Application&) = delete;
		Application& operator = (Application&&) = delete;

		// Виртуальный метод для инициализации и запуска приложения
		virtual int start(unsigned int window_width, unsigned int window_height, const char* title);

		// Виртуальный метод для обновления состояния приложения в каждом кадре
		virtual void on_update() {}
	};

}