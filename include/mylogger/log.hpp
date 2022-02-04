#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <mylogger_export.h>
#include <spdlog/spdlog.h>
namespace mylogger
{
using Logger = std::shared_ptr<spdlog::logger>;

void MYLOGGER_EXPORT init(size_t q_size, size_t thread_count);
void MYLOGGER_EXPORT initSinks(const std::vector<spdlog::sink_ptr> &default_sinks);
Logger MYLOGGER_EXPORT createOrGet(const std::string &name);

} // namespace mylogger
