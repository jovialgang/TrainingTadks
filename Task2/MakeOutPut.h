#include <filesystem>

int countFiles(const std::filesystem::path& list);

void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile);

//std::vector<std::filesystem::path> tryParseComponent(std::filesystem::path component);

std::vector<std::filesystem::path>::iterator tryParseComponent(const std::filesystem::path& component, std::vector<std::filesystem::path>::iterator iter);