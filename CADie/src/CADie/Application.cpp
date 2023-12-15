#include "pch.h"
#include "Application.h"

#include "CADie/Events/ApplicationEvent.h"
#include "CADie/Log.h"
#include "CADie/Input.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include "GLAD/glad.h"

namespace CADie {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//VERTEX ARRAY OBJECT
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		//DATA
		float vertices[3 * 8] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
			- 0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f
		};

		//CREATING THE VERTEX BUFFER
		m_VertexBuffer.reset(new OpenGLVertexBuffer(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
		
		//CREATING THE INDEX BUFFER
		uint32_t indices[36] = { 0, 1, 2, 0, 2, 3, 1, 2, 6, 1, 5, 6, 0, 1, 4, 1, 5, 4, 3, 7, 2, 2, 6, 7, 0, 3, 7, 0, 4, 7, 4, 5, 7, 5, 6, 7 };
		m_IndexBuffer.reset(new OpenGLIndexBuffer(indices, 36));

		//CREATING THE SHADER
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			
			void main() 
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string shaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			void main() 
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, shaderSrc));

		Unbind(m_VertexBuffer);
		Unbind(m_IndexBuffer);
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.f, 0.f, 0.f, 1.00f);
			glClear(GL_COLOR_BUFFER_BIT);

			Bind(m_VertexBuffer);
			Bind(m_IndexBuffer);

			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, GetCount(m_IndexBuffer), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate(); //glfw polls for events and fires the callback function/method Application::OnEvent
		}
	}
}