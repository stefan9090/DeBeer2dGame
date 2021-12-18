//
// Created by beerd on 12/14/2021.
//

#include "Logger.h"

#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/stdout_color_sinks.h"

void Logger::init()
{
    auto console = spdlog::stdout_color_mt("console");
    auto consoleSink = dynamic_cast<spdlog::sinks::stdout_color_sink_mt *>(console->sinks().back().get());
    spdlog::set_default_logger(console);
    spdlog::set_pattern("%^[%H:%M:%S][%-19s:%#][%-5l] %v%$");

    consoleSink->set_color_mode(spdlog::color_mode::always);
}