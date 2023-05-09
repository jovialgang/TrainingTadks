#include <filesystem>
#include <mutex>
#include <vector>
#include <shared_mutex>
#include <future>


struct Params {
    std::vector<std::filesystem::path> Files;   // список файлов
    std::mutex Mtx;
    std::filesystem::path CurrentDir;   // текущая директория
    std::condition_variable CV;
    std::future<void> FirstFuture;
    std::future<void> SecondFuture;
    bool Ready = false;     // условие блокировки/освобождения потоков
    bool StopWriteFiles = true;
};

void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile);

void writeFiles(const std::shared_ptr<Params>& ptr);

void findDirs(const std::filesystem::path& component, const std::shared_ptr<Params>& ptr);
