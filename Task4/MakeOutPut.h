#include <filesystem>
#include <mutex>
#include <vector>
#include <shared_mutex>
#include <future>

void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile);

std::vector<std::filesystem::path> parseComponent(const std::filesystem::path& component);

