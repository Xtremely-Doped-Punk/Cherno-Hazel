#include "PrecompHead.h"
#include "Log.h"

using namespace spdlog;

namespace Hazel {


	std::shared_ptr<logger> Log::spd_CoreLogger;
	std::shared_ptr<logger> Log::spd_ClientLogger;
	char* Log::pattern;

	void Log::Init(const char* pattern_str)
	{
		pattern = (char*)pattern_str;
		set_pattern(pattern);
		/*	"%^[%D %r] %5!n[%7!s|%-7!!]: (%L)%$ %v" --> my format:

			%D or %x -> Short MM/DD/YY date
			%T or %X -> 24hrs TimeStamp
			%r -> 12hr am/pm format
			%l or %L -> log level (info/I, debug/D, etc)
			%^any%$ -> Start & End of ColorRange
			%5!n -> LoggerName with width=5, right-allign & truncated
			%v -> ActualText
			%s and %! -> source file & function */

		if (!spd_CoreLogger)
			spd_CoreLogger = stdout_color_mt("HAZEL");
		spd_CoreLogger->set_level(level::trace); // debug everything in engine
		
		if (!spd_ClientLogger)
			spd_ClientLogger = stdout_color_mt("APP");
		spd_ClientLogger->set_level(level::trace);
	}
}