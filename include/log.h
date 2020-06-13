#ifndef LOG_H
#define LOG_H

#include <spdlog/spdlog.h>

class Log {
  public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

  private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
};

#define SIMCS_LOG_TRACE(...)   ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SIMCS_LOG_DEBUG(...)   ::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define SIMCS_LOG_INFO(...)   ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SIMCS_LOG_WARN(...)   ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SIMCS_LOG_ERROR(...)  ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SIMCS_LOG_CRITICAL(...)   ::Log::GetCoreLogger()->critical(__VA_ARGS__)


#endif