#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/cfg/env.h>
#include "mylogger/log.hpp"

#include <iostream>

namespace mylogger
{

struct Context
{
    std::vector<spdlog::sink_ptr> default_sinks;
    ~Context()
    {
        spdlog::shutdown();
    }
};

static Context context;

void MYLOGGER_EXPORT init(size_t q_size, size_t thread_count)
{
    spdlog::init_thread_pool(q_size, thread_count);
    spdlog::set_automatic_registration(true);
    spdlog::cfg::load_env_levels();
    spdlog::set_error_handler(
        [](const std::string &msg) { createOrGet("debug")->error("*** LOGGER ERROR ***: {}", msg); });
}

void MYLOGGER_EXPORT initSinks(const std::vector<spdlog::sink_ptr> &default_sinks)
{
    context.default_sinks = default_sinks;
}

Logger MYLOGGER_EXPORT createOrGet(const std::string &name)
{
    auto logger = spdlog::get(name);
    if (!logger)
    {
        logger = std::make_shared<spdlog::logger>(name, context.default_sinks.begin(), context.default_sinks.end());
        spdlog::initialize_logger(logger);
    }
    return logger;
}
} // namespace mylogger
