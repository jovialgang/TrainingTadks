#include "MakeOutPut.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

int countFiles(const std::filesystem::path& list){      // считаем общее количество файлов
    static int files_count = 0;
    for (auto file : std::filesystem::directory_iterator(list)){
        if (file.is_directory()){
            countFiles(file);
        } else if (file.is_regular_file()){
            files_count++;
        }
    }
    return files_count;
}


void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile) {

    std::ofstream fout(outPutFile);   // выходной файл
    std::vector<std::filesystem::path> files;
    files.resize(countFiles(list));     // задаём размер вектора
    auto iter = tryParseComponent(list, files.begin());     // оттправляем в функцию итератор на первый элемент списка
    sort(files.begin(), files.end());
    for (std::filesystem::path& path : files){
        fout << path.string() << std::endl;     // выводим в файл
    }
}


std::vector<std::filesystem::path>::iterator tryParseComponent(const std::filesystem::path& component, std::vector<std::filesystem::path>::iterator iter) {
    for (auto& anyPath: std::filesystem::directory_iterator(component)) {    // перебираем все компоненты в указанной директории
        if (anyPath.is_directory()) {    // если директория
           iter = tryParseComponent(anyPath.path(), iter); // запускаемся от неё рекурсивно
        } else if (anyPath.is_regular_file()) {     // если файл, сохраняем
           *iter = anyPath.path();  // разыменовываем указатель и записываем на этот адресс значение
           iter++;      // передвигаем указатель на следующий элемент
        }
    }
    return iter;
}
