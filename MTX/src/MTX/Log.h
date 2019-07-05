#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Container class for spdlog ///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace MTX {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define MTX_CORE_TRACE(...)    ::MTX::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MTX_CORE_INFO(...)     ::MTX::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MTX_CORE_WARN(...)     ::MTX::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MTX_CORE_ERROR(...)    ::MTX::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MTX_CORE_CRITICAL(...) ::MTX::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client Log Macros
#define MTX_TRACE(...)		  ::MTX::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MTX_INFO(...)		  ::MTX::Log::GetClientLogger()->info(__VA_ARGS__)
#define MTX_WARN(...)		  ::MTX::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MTX_ERROR(...)		  ::MTX::Log::GetClientLogger()->error(__VA_ARGS__)
#define MTX_CRITICAL(...)	  ::MTX::Log::GetClientLogger()->critical(__VA_ARGS__)