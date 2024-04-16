// Защита от множественного включения заголовочного файла
#pragma once

//#include "KeyEngineCore\Log.hpp"

#include <functional>
#include <array>

// Объявление пространства имен KeyEngine для вашего движка
namespace KeyEngine {
	
	// Перечисление типов событий
	enum class EventType
	{
		WindowResize = 0,
		WindowClose,

		KeyPressed,
		KeyReleased,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,

		EventsCount
	};

	// Базовая структура для событий
	struct BaseEvent
	{
		virtual ~BaseEvent() = default;
		virtual EventType get_type() const = 0;
	};

	// Класс для диспетчеризации событий
	class EventDispatcher
	{
	public:
		// Метод для добавления обработчика событий
		template<typename EventType>
		void add_event_listener(std::function<void(EventType)> callback)
		{
			// Создаем обертку для обработчика события, принимающую базовое событие
			auto baseCallback = [func = std::move(callback)](BaseEvent& e)
			{
				// Проверяем тип события и вызываем обработчик события, если тип совпадает
				if (e.get_type() == EventType::type)
				{
					func(static_cast<EventType&>(e));
				}
			};

			// Сохраняем обернутый обработчик в массиве обработчиков
			m_eventCallbacks[static_cast<size_t>(EventType::type)] = std::move(baseCallback);
		}

		// Метод для диспетчеризации события
		void dispatch(BaseEvent& event)
		{
			// Получаем обработчик события по типу и вызываем его
			auto& callback = m_eventCallbacks[static_cast<size_t>(event.get_type())];

			if (callback)
			{
				callback(event);
			}
		}

	private:
		// Массив обработчиков событий
		std::array<std::function<void(BaseEvent&)>, static_cast<size_t>(EventType::EventsCount)> m_eventCallbacks;
	};

	// Структура для события "Мышь перемещена"
	struct EventMouseMoved : public BaseEvent
	{
		EventMouseMoved(const double new_x, const double new_y)
			: x(new_x)
			, y(new_y)
		{
		}

		virtual EventType get_type() const override
		{
			return type;
		}

		double x; // Координата X
		double y; // Координата Y

		static const EventType type = EventType::MouseMoved; // Тип события
	};

	// Структура для события "Изменение размера окна"
	struct EventWindowResize : public BaseEvent
	{
		EventWindowResize(const unsigned int new_width, const unsigned int new_height)
			: width(new_width)
			, height(new_height)
		{
		}

		virtual EventType get_type() const override
		{
			return type;
		}

		unsigned int width;  // Новая ширина окна
		unsigned int height; // Новая высота окна

		static const EventType type = EventType::WindowResize; // Тип события
	};

	// Структура для события "Закрытие окна"
	struct EventWindowClose : public BaseEvent
	{
		virtual EventType get_type() const override
		{
			return type;
		}

		static const EventType type = EventType::WindowClose; // Тип события
	};
}