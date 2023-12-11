#pragma once

#ifdef CADIE_PLATFORM_WINDOWS

extern CADie::Application* CADie::CreateApplication();

int main()
{
	CADie::Log::Init();
	CADIE_CORE_TRACE("Initialized Log!");
	CADIE_CLIENT_TRACE("Initialized Log!");
	auto app = CADie::CreateApplication();
	app->Run();
	delete app;
}

#endif