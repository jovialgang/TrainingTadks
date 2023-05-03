#include "MakeOutPut.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <memory>
#include <future>
#include <mutex>
#include <iostream>


void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile) {

    std::vector<std::future<void>> futures;     //  мы не возвращаем значения из tryParseComponent, поэтому и тут void
    std::vector<std::filesystem::path> directories;     // список каталогов

    directories.push_back(list);
    findDir(list, directories);
    std::shared_ptr<Params> params_ptr = std::make_shared<Params>();     // создаём умный указатель

    for (std::filesystem::path& dir : directories){     // запускаем функцию асинхронно для каждого каталога
        futures.push_back(std::async(std::launch::async, tryParseComponent, std::ref(dir), params_ptr));
    }

    for (auto& f : futures){    // ждём завершения всех задач
        f.wait();
    }


    std::ofstream fout(outPutFile);   // выходной файл
    sort(params_ptr->Files.begin(), params_ptr->Files.end());
    for (std::filesystem::path& path : params_ptr->Files){
        fout << path.string() << std::endl;     // выводим в файл
    }
}



void findDir(const std::filesystem::path& component, std::vector<std::filesystem::path>& directories){   // собираем список всех каталогов, чтобы
    for (auto& anyPath: std::filesystem::directory_iterator(component)) {       // запустить каждый каталог потом в отдельном пототке
        if (anyPath.is_directory()) {
            directories.push_back(anyPath.path());
           findDir(anyPath.path(), directories);
        }
    }
}


void tryParseComponent(const std::filesystem::path& component, const std::shared_ptr<Params>& ptr) {
    for (auto& anyPath: std::filesystem::directory_iterator(component)) {    // перебираем все компоненты в указанной директории
        if (anyPath.is_directory()) {    // если директория
            continue;
        } else if (anyPath.is_regular_file()) {     // если файл
            std::lock_guard<std::mutex> lock(ptr->Mtx);      //  создаёт объект который, блокирует мьютекс и разблокирует его при уничтожении объекта
            ptr->Files.push_back(anyPath.path());     // сохраняем
//            std::cout << std::this_thread::get_id() << std::endl;  // проверка, что выполняют разные пототки
        }
    }
}

