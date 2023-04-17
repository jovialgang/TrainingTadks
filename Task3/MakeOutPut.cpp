#include "MakeOutPut.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <iostream>


void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile) {

    std::vector<std::future<void>> futures;     //  вы не возвращаяем значения из tryParseComponen, поэтому и тут void
    std::vector<std::filesystem::path> directories;     // список каталогов
    std::vector<std::filesystem::path> files;       // итоговый ответ
    std::mutex mtx;     // мьютекс

    findDir(list, directories);

    for (std::filesystem::path& dir : directories){     // запускаем функцию асинхронно для каждого каталога
        futures.push_back(std::async(std::launch::async, tryParseComponent, std::ref(dir), std::ref(files), std::ref(mtx)));

    }

    for (auto& f : futures){    // ждём завершения всех задач
        f.wait();
    }

    std::ofstream fout(outPutFile);   // выходной файл
    sort(files.begin(), files.end());
    for (std::filesystem::path& path : files){
        fout << path.string() << std::endl;     // выводим в файл
    }
}



void findDir(const std::filesystem::path& component,std::vector<std::filesystem::path>& directories){   // собираем список всех каталогов, чтобы
    for (auto& anyPath: std::filesystem::directory_iterator(component)) {       // запустить каждый каталог потом в отдельном пототке
        if (anyPath.is_directory()) {
            directories.push_back(anyPath.path());
           findDir(anyPath.path(), directories);
        }
    }
}



void tryParseComponent(const std::filesystem::path& component, std::vector<std::filesystem::path>& files, std::mutex& mtx) {
    for (auto& anyPath: std::filesystem::directory_iterator(component)) {    // перебираем все компоненты в указанной директории
        if (anyPath.is_directory()) {    // если директория
            continue;
        } else if (anyPath.is_regular_file()) {     // если файл
            std::lock_guard<std::mutex> lock(mtx);      //  создаёт объект который блокирует мьютекс и разблокирует его при уничтожении объекта
            files.push_back(anyPath.path());     // сохраняем
//            std::cout << std::this_thread::get_id() << std::endl;  // проверка, что выполняют разные пототки
        }
    }
}
