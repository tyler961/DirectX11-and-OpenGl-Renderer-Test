#include "pch.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// **********************************************************************************************
// Must call Init() to use logs. 
// Using the macros from Log.h, example usage is as such: MTX_CORE_ERROR("Error, {0}", error);
// spdlog at github has documentation if you'd like to change the set_pattern parameters
// **********************************************************************************************


namespace MTX {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// [%T] = Time 
		// %n = name of logger 
		// %v%$ = logger message
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("VAPR");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}