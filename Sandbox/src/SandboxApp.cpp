#include <CADie.h>

class ExampleLayer : public CADie::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{

	}

	void OnEvent(CADie::Event& event) override
	{
		if (event.GetEventType() == CADie::EventType::KeyPressed)
		{
			CADie::KeyPressedEvent& e = (CADie::KeyPressedEvent&)event;
			CADIE_CORE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public CADie::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new CADie::ImGuiLayer());
	};
	~Sandbox()
	{

	};
};

CADie::Application* CADie::CreateApplication()
{
	return new Sandbox();
};