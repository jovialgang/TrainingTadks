#include <iostream>
#include <condition_variable>
#include <mutex>
#include <filesystem>
#include <vector>
#include <shared_mutex>
#include <future>


struct Params {
    std::vector<std::filesystem::path> Files;
    std::mutex Mtx;
    std::shared_mutex SMtx;
    std::recursive_mutex RMtx;
    std::filesystem::path CurrentDir;
    std::condition_variable CV;
    std::string Test;
    bool Ready = false;
    std::future<void> FirstFuture;
    std::future<void> SecondFuture;
};

//void test1(const std::shared_ptr<Params>& ptr);

int test2(const std::shared_ptr<Params>& ptr);
