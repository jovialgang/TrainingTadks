#include <filesystem>
#include <mutex>

void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile);

void findDir(const std::filesystem::path& component,std::vector<std::filesystem::path>& directories);

void tryParseComponent(const std::filesystem::path& component, std::vector<std::filesystem::path>& files, std::mutex& mtx);