#pragma once

#include "CADie/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace CADie {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}
