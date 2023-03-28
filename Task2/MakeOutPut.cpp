#include "MakeOutPut.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>


void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile) {
    std::ofstream fout(outPutFile);   // выходной файл
    std::vector<std::filesystem::path> files;
    files = tryParseComponent(list); // тут храним найденные пути
    sort(files.begin(), files.end());
    for (std::filesystem::path& path : files){
        fout << path.string() << std::endl;     // выводим в файл
    }
}

std::vector<std::filesystem::path> tryParseComponent(std::filesystem::path component) {
    static std::vector<std::filesystem::path> files;
    for (auto& anyPath: std::filesystem::directory_iterator(component)) {    // перебираем все компоненты в указанной директории
        if (anyPath.is_directory()) {    // если директория
            files = tryParseComponent(anyPath.path()); // запускаемся от неё рекурсивно
        } else if (anyPath.is_regular_file()) {     // если файл, сохраняем
            files.push_back(anyPath.path());
        }
    }
    return files;
}