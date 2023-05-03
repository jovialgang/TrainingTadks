#include <filesystem>
#include <mutex>
#include <vector>


struct Params {
    std::vector<std::filesystem::path> Files;
    std::mutex Mtx;
};

void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile);

void findDir(const std::filesystem::path& component,std::vector<std::filesystem::path>& directories);

void tryParseComponent(const std::filesystem::path& component, const std::shared_ptr<Params>& ptr);
