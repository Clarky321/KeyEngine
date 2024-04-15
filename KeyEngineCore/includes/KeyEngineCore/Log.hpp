// Защита от множественного включения заголовочного файла
#pragma once

// Включение заголовочного файла библиотеки spdlog
#include <spdlog\spdlog.h>

// Объявление пространства имен KeyEngine для вашего движка
namespace KeyEngine {

// Условная компиляция в зависимости от режима сборки
#ifdef NDEBUG

// Если NDEBUG определен (режим релиза), определите макросы логирования как пустые
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_CRITICAL(...)

#else

// Если NDEBUG не определен (режим отладки), определите макросы логирования как вызовы функций из библиотеки spdlog

// Макрос для логирования информационных сообщений
#define LOG_INFO(...)	spdlog::info(__VA_ARGS__)

// Макрос для логирования предупреждающих сообщений
#define LOG_WARN(...)	spdlog::warn(__VA_ARGS__)

// Макрос для логирования сообщений об ошибках
#define LOG_ERROR(...)	spdlog::error(__VA_ARGS__)

// Макрос для логирования критических сообщений
#define LOG_CRITICAL(...)	spdlog::critical(__VA_ARGS__)

#endif // NDEBUG

}