#include "KeyEngineCore\Window\Window.hpp"
#include "KeyEngineCore\Log.hpp"

#include "KeyEngineCore\Rendering\OpenGL\ShaderProgram\ShaderProgram.hpp"
#include "KeyEngineCore\Rendering\OpenGL\VertexBuffer\VertexBuffer.hpp"
#include "KeyEngineCore\Rendering\OpenGL\VertexArray\VertexArray.hpp"
#include "KeyEngineCore\Rendering\OpenGL\IndexBuffer\IndexBuffer.hpp"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <imgui\imgui.h>
#include <imgui\backends\imgui_impl_opengl3.h>
#include <imgui\backends\imgui_impl_glfw.h>

#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>

namespace  KeyEngine {

    static bool s_GLFW_initialized = false;

    GLfloat positions_colors2[] = {
       -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 1.0f,
       -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2, 3, 2, 1
    };

    const char* vertex_shader =
        R"(#version 460
           layout(location = 0) in vec3 vertex_position;
           layout(location = 1) in vec3 vertex_color;
           uniform mat4 model_matrix;
           out vec3 color;
           void main() {
              color = vertex_color;
              gl_Position = model_matrix * vec4(vertex_position, 1.0);
           })";

    const char* fragment_shader =
        R"(#version 460
           in vec3 color;
           out vec4 frag_color;
           void main() {
              frag_color = vec4(color, 1.0);
           })";

    std::unique_ptr<ShaderProgram> p_shader_program;
    std::unique_ptr<VertexBuffer> p_positions_colors_vbo;
    std::unique_ptr<IndexBuffer> p_index_buffer;
    std::unique_ptr<VertexArray> p_vao;

    float scale[3] = { 1.f, 1.f, 1.f };
    float rotate = 0.f;
    float translate[3] = { 0.f, 0.f, 0.f };

	Window::Window(std::string title, const unsigned int width, const unsigned int height)
		: m_data({ std::move(title), width, height })
	{
		int resultCode = init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true); 
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

        glfwSetFramebufferSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                glViewport(0, 0, width, height);
            }
        );

        p_shader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);

        if (!p_shader_program->isCompiled())
        {
            return false;
        }

        BufferLayout buffer_layout_1vec3{ ShaderDataType::Float3 };

        BufferLayout buffer_layout_2vec3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3
        };

        p_vao = std::make_unique<VertexArray>();
        p_positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors2, sizeof(positions_colors2), buffer_layout_2vec3);
        p_index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

        p_vao->add_vertex_buffer(*p_positions_colors_vbo);
        p_vao->set_index_buffer(*p_index_buffer);

        glm::mat3 mat_1(4, 0, 0, 2, 8, 1, 0, 1, 0);

        glm::mat3 mat_2(4, 2, 9, 2, 0, 4, 1, 4, 2);

        glm::mat3 result_mat = mat_1 * mat_2;

        LOG_INFO("");
        LOG_INFO("|{0:3} {1:3} {2:3}|", result_mat[0][0], result_mat[1][0], result_mat[2][0]);
        LOG_INFO("|{0:3} {1:3} {2:3}|", result_mat[0][1], result_mat[1][1], result_mat[2][1]);
        LOG_INFO("|{0:3} {1:3} {2:3}|", result_mat[0][2], result_mat[1][2], result_mat[2][2]);
        LOG_INFO("");

        glm::vec4 vec(1, 2, 3, 4);
        glm::mat4 mat_identity(1);

        glm::vec4 result_vec = mat_identity * vec;

        LOG_INFO("({0} {1} {2} {3})", result_vec[0], result_vec[1], result_vec[2], result_vec[3]);

        return 0;
	}

	void Window::shutdown()
	{
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
	}

	void Window::on_update()
	{
        glClearColor(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);



        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        //ImGui::ShowDemoWindow();

        ImGui::Begin("Background Color Window");
        ImGui::ColorEdit4("Background Color", m_background_color);

        ImGui::SliderFloat3("scale", scale, 0.f, 2.f);
        ImGui::SliderFloat("rotate", &rotate, 0.f, 360.f);
        ImGui::SliderFloat3("translate", translate, -1.f, 1.f);

        p_shader_program->bind();

        glm::mat4 scale_matrix(scale[0], 0,        0,        0,
                               0,        scale[1], 0,        0,
                               0,        0,        scale[2], 0,
                               0,        0,        0,        1);

        float rotate_in_radians = glm::radians(rotate);

        glm::mat4 rotate_matrix( cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
                                -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
                                 0,                      0,                      1, 0,
                                 0,                      0,                      0, 1);

        glm::mat4 translate_matrix(1,            0,            0,            0,
                                   0,            1,            0,            0,
                                   0,            0,            1,            0,
                                   translate[0], translate[1], translate[2], 1);

        glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;
        p_shader_program->setMatrix4("model_matrix", model_matrix);

        p_vao->bind();

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_vao->get_indices_count()), GL_UNSIGNED_INT, nullptr);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
	}
}