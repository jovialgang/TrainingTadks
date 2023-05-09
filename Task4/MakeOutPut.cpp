#include "MakeOutPut.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <memory>
#include <future>
#include <shared_mutex>
#include <iostream>


void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile) {

    std::shared_ptr<Params> params_ptr = std::make_shared<Params>();     // создаём умный указатель

    // создаём два потока
    params_ptr->FirstFuture = std::async(std::launch::async, findDirs, std::ref(list), params_ptr);
    params_ptr->SecondFuture = std::async(std::launch::async, writeFiles, params_ptr);

    params_ptr->FirstFuture.wait();     // ожидаем завершение первого потока
    params_ptr->StopWriteFiles = false;     // останавливаем цикл while в writeFiles
    params_ptr->Ready = true;
    params_ptr->CV.notify_one();    // разблокируем поток, чтобы выйти из функции
    params_ptr->SecondFuture.wait();    // ожидаем завершение второго потока




    std::ofstream fout(outPutFile);   // выходной файл
    sort(params_ptr->Files.begin(), params_ptr->Files.end());
    for (std::filesystem::path& path : params_ptr->Files){
        fout << path.string() << std::endl;     // выводим в файл
    }
}

void writeFiles(const std::shared_ptr<Params>& ptr) {   // функция, которая считывает файлы
    while (ptr->StopWriteFiles) {   // цикл, который мы потом остановим с помощью false
        std::unique_lock<std::mutex> lock(ptr->Mtx);
        ptr->CV.wait(lock, [&ptr] { return ptr->Ready; });  // останавливаем поток с помощью std::condition_variable
        ptr->Ready = false;
        for (auto &anyPath: std::filesystem::directory_iterator(    // стандартно перебираем компоненты
                ptr->CurrentDir)) {    // работаем с каталогом, который получили в функции findDirs
            if (anyPath.is_directory()) {
                continue;
            } else if (anyPath.is_regular_file()) {
                ptr->Files.push_back(anyPath.path());
            }
        }

    }
}

void findDirs(const std::filesystem::path& component, const std::shared_ptr<Params>& ptr){
    for (auto& anyPath: std::filesystem::directory_iterator(component)) {       // запустить каждый каталог потом в отдельном пототке
        if (anyPath.is_directory()) {
            ptr->CurrentDir = anyPath;  // сохраняем текущий каталог
            ptr->Ready = true;
            ptr->CV.notify_one();   // разблокируем поток в функции writeFiles
            findDirs(anyPath, ptr);
        }
    }
}
