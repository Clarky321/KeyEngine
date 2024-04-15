#include "KeyEngineCore\Window.hpp"
#include "KeyEngineCore\Log.hpp"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace  KeyEngine {

    static bool s_GLFW_initialized = false;

	Window::Window(std::string title, const unsigned int width, const unsigned int height)
		: m_data({ std::move(title), width, height })
	{
		int resultCode = init();
	}

	Window::~Window()
	{
		shutdown();
	}

    int Window::init()
    {
        LOG_INFO("Creating window '{0}' width size {1}x{2}", m_data.title, m_data.width, m_data.height);

        if (!s_GLFW_initialized)
        {
            if (!glfwInit())
            {
                LOG_CRITICAL("Can`t initialize GLFW");

                return -1;
            }
            s_GLFW_initialized = true;
        }

        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);

        if (!m_pWindow)
        {
            LOG_CRITICAL("Can`t create window {0} width size {1}x{2}", m_data.title, m_data.width, m_data.height);

            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to initialize GLAD");

            return -3;
        }

        glfwSetWindowUserPointer(m_pWindow, &m_data);

        glfwSetWindowSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.width = height;

                EventWindowResize event(width, height);
                data.eventCallbackFn(event);
            }
        );


        glfwSetCursorPosCallback(m_pWindow,
            [](GLFWwindow* pWindow, double x, double y)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventMouseMoved event(x, y);
                data.eventCallbackFn(event);
            }
        );

        glfwSetWindowCloseCallback(m_pWindow,
            [](GLFWwindow* pWindow)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventWindowClose event;
                data.eventCallbackFn(event);
            }
        );

        return 0;
	}

	void Window::shutdown()
	{
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
	}

	void Window::on_update()
	{
        glClearColor(1, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
	}
}