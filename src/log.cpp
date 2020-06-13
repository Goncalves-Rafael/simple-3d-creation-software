#include "spdlog/sinks/stdout_color_sinks.h"

#include "log.h"

 std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

void Log::init () {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  s_CoreLogger = spdlog::stdout_color_mt("SIMCS");
  s_CoreLogger->set_level(spdlog::level::trace);
}