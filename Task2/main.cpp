#include <iostream>
#include <filesystem>
#include <algorithm>
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


    auto found_list = std::find(args.begin(), args.end(), "--list");    // находим указатели на нужные нам параметры
    auto found_output = std::find(args.begin(), args.end(), "--output_file");

    if (found_list != args.end() && found_output != args.end()){     // если хотя бы один указывает на .end() значит параметры не найдены
        list = *(found_list+1);
        outPath = *(found_output+1);
        makeOutPutFle(list, outPath);
        return 0;
    }

    auto found_generate = std::find(args.begin(), args.end(), "--generate");    // идентично предыдущему блоку
    auto found_treeDepth = std::find(args.begin(), args.end(), "--tree_depth");
    auto found_filesCount = std::find(args.begin(), args.end(), "--files_count");


    if (found_generate != args.end() && found_treeDepth != args.end() && found_filesCount != args.end()){
        generate = *(found_generate+1);
        treeDepth = std::stoi(*(found_treeDepth+1));
        filesCount = std::stoi(*(found_filesCount+1));
        generateTree(generate, treeDepth, filesCount);
        return 0;
    }

    return 0;
}
