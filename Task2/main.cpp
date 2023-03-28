#include <iostream>
#include <filesystem>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include "GenerateTree.h"
#include "MakeOutPut.h"

int main(int argc, char* argv[]) {

    std::vector<std::string> args;
    args.resize(argc);
    for (int i = 0; i < argc; i++){
        args[i] = argv[i];
    }


    std::filesystem::path list, outPath, generate;
    int treeDepth, filesCount;


    bool found_list = std::find(args.begin(), args.end(), "--list") != args.end();
    bool found_output = std::find(args.begin(), args.end(), "--output_file") != args.end();
    if (found_list & found_output){
        list = args[found_list+1];
        outPath = args[found_output+1];
        makeOutPutFle(list, outPath);
    }

    bool found_generate = std::find(args.begin(), args.end(), "--generate") != args.end();
    bool found_treeDepth = std::find(args.begin(), args.end(), "--tree_depth") != args.end();
    bool found_filesCount = std::find(args.begin(), args.end(), "--files_count") != args.end();

    if (found_generate & found_treeDepth & found_filesCount){
        generate = args[found_generate+1];
        std::cout << generate << args[found_treeDepth+1] << args[found_filesCount+1] << std::endl;
        treeDepth = std::stoi(args[found_treeDepth+1]);
        filesCount = std::stoi(args[found_filesCount+1]);
        generateTree(generate, treeDepth, filesCount);
    }


    // парсим аргументы командной строки
//    switch (argc) {     // выбор режима работы программы
//        case 5 : // если два входных параметра, то считываем дерево и записываем в выходной файл
//
//            bool check1, check2;
//            for (int i = 0; i < argc; i++){
//                if (argv[i] == std::string("--list")) {
//                    list = argv[i + 1];
//                    check1 = true;
//                }
//                if (argv[i] == std::string("--output_file")) {
//                    outPath = argv[i + 1];
//                    check2 = true;
//                }
//            }
//            if (check1 & check2) {
//                makeOutPutFle(list, outPath);  // отправляем наши параметры в функцию
//            } else{
//                std::cout << "Error: You have some problem... with set of arguments.";
//                return 0;   // я подумал, что писать контрукцию try catch громоздко и неуместно, так что сделал cout и return
//            }
//            break;
//
//        case 7 : //если 3 входных параметра, то строим дерево каталогов и файлов
//            bool check3, check4, check5;
//            for (int i = 0; i < argc; i++){
//                if (argv[i] == std::string("--generate")) {
//                    generate = argv[i + 1];
//                    check3 = true;
//                }
//                if (argv[i] == std::string("--tree_depth")) {
//                    treeDepth = std::atoi(argv[i + 1]);
//                    check4 = true;
//                }
//                if (argv[i] == std::string("--files_count")) {
//                    filesCount = std::atoi(argv[i + 1]);
//                    check5 = true;
//                }
//            }
//            if (check3 & check4 & check5) {
//                generateTree(generate, treeDepth, filesCount);// отправляем наши параметры в функцию
//            } else{
//                std::cout << "Error: You have some problem... with set of arguments.";
//                return 0;
//            }
//            break;
//
//        default:
//            std::cout << "Error: You have some problem... with quantity of arguments."; // тоже замена try catch на cout и return
//            return 0;   // просто чтобы знать из-за чего программа не работает
//            break;
//    }
    return 0;
}
