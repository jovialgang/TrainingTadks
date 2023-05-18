#include "MakeOutPut.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <memory>
#include <future>
#include <iostream>


void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile) {

    std::vector<std::filesystem::path> allFiles;

    allFiles = parseComponent(list);

    std::ofstream fout(outPutFile);   // выходной файл
    std::sort(allFiles.begin(), allFiles.end());
    for (std::filesystem::path& path : allFiles){
        fout << path.string() << std::endl;     // выводим в файл
    }

}

std::vector<std::filesystem::path> parseComponent(const std::filesystem::path& component){
    std::vector<std::filesystem::path> currentFiles;
    std::vector<std::future<std::vector<std::filesystem::path>>> futures;

    for (auto& anyPath: std::filesystem::directory_iterator(component)) {
        if (anyPath.is_directory()) {
            auto task = [anyPath]() {
                return parseComponent(anyPath.path());
            };
            futures.push_back(std::async(std::launch::async, task));
        } else if (anyPath.is_regular_file()){
            currentFiles.push_back(anyPath);
        }
    }

    for (auto & future : futures){
        future.wait();
        std::vector<std::filesystem::path> anyDir;
        anyDir = future.get();
        currentFiles.insert(currentFiles.end(), anyDir.begin(), anyDir.end());
    }

    return currentFiles;
}
