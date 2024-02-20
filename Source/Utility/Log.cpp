#include "epch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"


std::shared_ptr<spdlog::logger> ULog::sCoreLogger;
std::unordered_map<FUUID, std::shared_ptr<spdlog::logger>> ULog::sEventLoggers;

void ULog::Initialize()
{
	std::vector<spdlog::sink_ptr> sinks;
	sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Saved/Logs/Engine.log", true));

	sinks[0]->set_pattern("%^[%T][%@] %n: %v%$");
	sinks[1]->set_pattern("[%T] [%l] %n: %v");

	sCoreLogger = std::make_shared<spdlog::logger>("Engine", begin(sinks), end(sinks));
	spdlog::register_logger(sCoreLogger);
	sCoreLogger->set_level(spdlog::level::trace);
	sCoreLogger->flush_on(spdlog::level::trace);
}

FUUID ULog::RegisterEventLogger(const std::string& loggerName)
{
	std::string loggerLocation = "Saved/Logs/" + loggerName + ".log";

	spdlog::sink_ptr sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(loggerLocation, true);

	FUUID id{};

	sEventLoggers[id] = std::make_shared<spdlog::logger>(loggerName, sink);
	spdlog::register_logger(sEventLoggers[id]);
	sEventLoggers[id]->set_level(spdlog::level::trace);
	sEventLoggers[id]->flush_on(spdlog::level::trace);

	return id;
}
