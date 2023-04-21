#include "MakeOutPut.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <iostream>


void makeOutPutFle(const std::filesystem::path& list, const std::filesystem::path& outPutFile) {

    std::vector<std::future<void>> futures;     //  мы не возвращаем значения из tryParseComponent, поэтому и тут void
    std::vector<std::filesystem::path> directories;     // список каталогов
    std::vector<std::filesystem::path> files;       // итоговый ответ
    std::mutex mtx;     // мьютекс

    directories.push_back(list);
    findDir(list, directories);
    Params params(files, mtx);      // создаём объект структуры Params и инициализируем его поля

    for (std::filesystem::path& dir : directories){     // запускаем функцию асинхронно для каждого каталога
        futures.push_back(std::async(std::launch::async, tryParseComponent, std::ref(dir), std::ref(params)));
    }

    for (auto& f : futures){    // ждём завершения всех задач
        f.wait();
    }


    std::ofstream fout(outPutFile);   // выходной файл
    sort(params.Files.begin(), params.Files.end());
    for (std::filesystem::path& path : params.Files){
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


void tryParseComponent(const std::filesystem::path& component, Params params) {
    for (auto& anyPath: std::filesystem::directory_iterator(component)) {    // перебираем все компоненты в указанной директории
        if (anyPath.is_directory()) {    // если директория
            continue;
        } else if (anyPath.is_regular_file()) {     // если файл
            std::lock_guard<std::mutex> lock(params.Mtx);      //  создаёт объект который, блокирует мьютекс и разблокирует его при уничтожении объекта
            params.Files.push_back(anyPath.path());     // сохраняем
//            std::cout << std::this_thread::get_id() << std::endl;  // проверка, что выполняют разные пототки
        }
    }
}
