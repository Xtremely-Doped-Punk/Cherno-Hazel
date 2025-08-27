#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace spdlog;

namespace Hazel {

	class HAZEL_API Log
	{
	private:
		static char* pattern;
		static std::shared_ptr<logger> spd_CoreLogger;
		static std::shared_ptr<logger> spd_ClientLogger;

	public:
        static void Init(const char* pattern = "%^[%T] %n: %v%$"); // Tutorial format
		inline static std::shared_ptr<logger>& GetCoreLogger() { return spd_CoreLogger; }
		inline static std::shared_ptr<logger>& GetClientLogger() { return spd_ClientLogger; }
	};
}

// macros for speed logging & striping core debug code defs in release versions easily
// core logger in order of severity 
#define HZ_TRACE(...)  :: Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)   :: Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)   :: Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)  :: Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_FATAL(...)  :: Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)
// client logger in order of severity 
#define LOG_TRACE(...) :: Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)  :: Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)  :: Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) :: Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...) :: Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)