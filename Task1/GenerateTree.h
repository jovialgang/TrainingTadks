#include <filesystem>

void generateTree(std::filesystem::path& generatePath, int treeDepth, int filesCount);

void createFiles(std::filesystem::path pathForFiles, int filesCount);

void createDirectories(std::filesystem::path parent, int treeDepth);