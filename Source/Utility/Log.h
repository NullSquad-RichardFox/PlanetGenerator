#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)


class ULog
{
public:
	static void Initialize();
	static std::shared_ptr<spdlog::logger>& GetLogger() { return sCoreLogger; }

private:
	static std::shared_ptr<spdlog::logger> sCoreLogger;
};

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}


#define LOG_TRACE(...) ULog::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ULog::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ULog::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ULog::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ULog::GetLogger()->critical(__VA_ARGS__)

#define LOG(...) LOG_TRACE(__VA_ARGS__)
#define EVENT_LOG(...)

#define INTERNAL_ASSERT_IMPL(check, msg, ...) { if (!(check)) { LOG_ERROR(msg, __VA_ARGS__); __debugbreak(); } }
#define ASSERT(check, msg) INTERNAL_ASSERT_IMPL(check, "Assertion failed: {0}", msg)