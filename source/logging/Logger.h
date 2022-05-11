//
// Created by beerd on 12/14/2021.
//

#ifndef DEBEER2D_LOGGER_H
#define DEBEER2D_LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#define LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define LOG_WARNING(...) SPDLOG_WARN(__VA_ARGS__)
#define LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)

class Logger
{
public:
    Logger() = delete;
    static void init();
};


#endif //DEBEER2D_LOGGER_H
