#pragma once

#include "CADie/Window.h"

#include <GLFW/glfw3.h>

#include "CADie/Renderer/GraphicsContext.h"

namespace CADie {
	
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate();

		inline unsigned int GetWidth() const override { return m_Data.Width; };
		inline unsigned int GetHeight() const override { return m_Data.Height; };

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; };
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height = 0;
			bool VSync = true;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
