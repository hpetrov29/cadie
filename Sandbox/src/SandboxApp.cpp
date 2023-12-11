#include <CADie.h>

class ExampleLayer : public CADie::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//CADIE_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(CADie::Event& e) override
	{
		CADIE_CLIENT_TRACE("{0}", e);
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