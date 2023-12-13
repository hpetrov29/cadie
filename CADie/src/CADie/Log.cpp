#include "pch.h"
#include "CADie/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace CADie {


	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	void Log::Init()
	{
		// color | time stamp | logger name | logger message
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_coreLogger = spdlog::stdout_color_mt("CADIE");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("SANDBOX");
		s_clientLogger->set_level(spdlog::level::trace);

	};

}