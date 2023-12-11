#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"


#define CADIE_CORE_TRACE(...) ::CADie::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CADIE_CORE_INFO(...) ::CADie::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CADIE_CORE_WARN(...) ::CADie::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CADIE_CORE_ERROR(...) ::CADie::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CADIE_CORE_FATAL(...) ::CADie::Log::GetCoreLogger()->critical(__VA_ARGS__)
//#define CADIE_CORE_ASSERT(...) ::CADie::Log::GetCoreLogger()->error(__VA_ARGS__)

#define CADIE_CLIENT_TRACE(...) ::CADie::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CADIE_CLIENT_INFO(...) ::CADie::Log::GetClientLogger()->info(__VA_ARGS__)
#define CADIE_CLIENT_WARN(...) ::CADie::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CADIE_CLIENT_ERROR(...) ::CADie::Log::GetClientLogger()->error(__VA_ARGS__)
#define CADIE_CLIENT_FATAL(...) ::CADie::Log::GetCoreLogger()->critical(__VA_ARGS__)

namespace CADie {


	class CADIE_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; };
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};

}

