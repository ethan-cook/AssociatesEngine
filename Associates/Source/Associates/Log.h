#pragma once
#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Associates
{
	class ASSOC_API Log
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

//Core log Macros
#define ASSOC_CORE_TRACE(...) ::Associates::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ASSOC_CORE_INFO(...)  ::Associates::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ASSOC_CORE_WARN(...)  ::Associates::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ASSOC_CORE_ERROR(...) ::Associates::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ASSOC_CORE_FATAL(...) ::Associates::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log Macros

#define ASSOC_TRACE(...) ::Associates::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ASSOC_INFO(...)  ::Associates::Log::GetClientLogger()->info(__VA_ARGS__)
#define ASSOC_WARN(...)  ::Associates::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ASSOC_ERROR(...) ::Associates::Log::GetClientLogger()->error(__VA_ARGS__)
#define ASSOC_FATAL(...) ::Associates::Log::GetClientLogger()->fatal(__VA_ARGS__)
