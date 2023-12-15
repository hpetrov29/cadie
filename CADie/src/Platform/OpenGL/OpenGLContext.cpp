#include "pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace CADie {

	

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		CADIE_CORE_INFO("OpenGL Info:");
		CADIE_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		CADIE_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		CADIE_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowHandle);
	}

}