#include <iostream>
#include <condition_variable>
#include <mutex>
#include <filesystem>
#include <vector>
#include <shared_mutex>
#include <future>
#include "main.h"


int count = 0;

//void test1(const std::shared_ptr<Params>& ptr){
//    count++;
//    ptr->Ready = true;
//    ptr->CV.notify_one();
//
////    std::cout << ptr->Test << "one" << std::endl;
//    std::unique_lock<std::mutex> lock(ptr->Mtx);
//    lock.lock();
//    ptr->Test += "a";
//    lock.unlock();
//    std::cout << "one" << std::endl;
//    if (count < 20){
//        test2(ptr);
//    }
//}

int test2(const std::shared_ptr<Params>& ptr){

    return 444555;
}
//void test3(const std::shared_ptr<Params>& ptr){
//    ptr->CV.notify_one();
//}

int main() {
    std::vector<std::future<void>> futures;     //  мы не возвращаем значения из tryParseComponent, поэтому и тут void

    std::shared_ptr<Params> params_ptr = std::make_shared<Params>();
//    params_ptr->FirstFuture = (std::async(std::launch::async, test1, params_ptr));
    auto future = (std::async(std::launch::async, test2, params_ptr));

    std::cout << future.get() << std::endl;


    return 0;
}
