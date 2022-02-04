#include <mylogger/log.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char const *argv[])
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    mylogger::init(8192, 2);
    mylogger::initSinks({std::make_shared<spdlog::sinks::stdout_color_sink_mt>()});
    auto log = mylogger::createOrGet("mylogger");

    const auto workers = {"anil", "busara", "carl", "ruslan", "leila", "bronislav", "sofia", "gülay", "edurne"};
    auto work = [](std::string name) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // wait a bit to bootstrap threads
        auto log = mylogger::createOrGet(name);
        for (int i = 0; i < 10; i++)
            log->info("hello!");
    };

    log->info("start...");
    std::vector<std::thread> threads;
    for (auto const &worker : workers)
    {
        threads.emplace_back(work, worker);
    }
    for (auto &thread : threads)
    {
        thread.join();
    }
    log->info("finish...");
    return 0;
}
