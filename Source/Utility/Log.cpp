#include "epch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"


std::shared_ptr<spdlog::logger> ULog::sCoreLogger;

void ULog::Initialize()
{
	std::vector<spdlog::sink_ptr> sinks;
	sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Saved/Logs/Engine.log", true));

	sinks[0]->set_pattern("%^[%T][%@] %n: %v%$");
	sinks[1]->set_pattern("[%T] [%l] %n: %v");

	sCoreLogger = std::make_shared<spdlog::logger>("Log", begin(sinks), end(sinks));
	spdlog::register_logger(sCoreLogger);
	sCoreLogger->set_level(spdlog::level::trace);
	sCoreLogger->flush_on(spdlog::level::trace);
}