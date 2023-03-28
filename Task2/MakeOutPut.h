#include <filesystem>

void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile);

std::vector<std::filesystem::path> tryParseComponent(std::filesystem::path component);