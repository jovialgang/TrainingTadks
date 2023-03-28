#include <string>
#include <filesystem>
#include <fstream>
#include <random>
#include "GenerateTree.h"

void generateTree(std::filesystem::path generatePath, int treeDepth, int filesCount){

    std::filesystem::create_directory(generatePath);    // создаём "домушнюю" директорию

    createDirectories(generatePath, treeDepth);     // создаём папки

    createFiles(generatePath, filesCount);      // создаём файлы

}

void createFiles(std::filesystem::path pathForFiles, int filesCount){
    for (const std::filesystem::directory_entry& anyPath: std::filesystem::directory_iterator(pathForFiles)) {    // перебираем все компоненты в указанной директории
        if (anyPath.is_directory()) {    // если директория
            createFiles(anyPath.path(), filesCount); // запускаемся от неё рекурсивно
        } else if (anyPath.is_regular_file()) {
            continue;
        }
        for (int i = 1; i <= filesCount; i++){
            std::ofstream file(anyPath.path().string() + std::to_string(i) + ".txt");   // собственно, создание конкретного файла
        }
    }
}


void createDirectories(std::filesystem::path parent, int treeDepth){

    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> dis(1,9);    // создаём рандомайзер

    if (treeDepth <= 0){     // создаём условие выхода из функции
        return;
    }

    if (!std::filesystem::exists(parent)){      // проверка наличия директории, от которой мы запустились
         std::filesystem::create_directory(parent);     // создание директории по имени, которое мы создали в предыдущей итерации
    }

    std::string dirName = "";
    dirName += "Child" + std::to_string(dis(gen));      // создание имени директории
    std::filesystem::path childPath = parent / dirName;
    createDirectories(childPath, treeDepth - 1);

}