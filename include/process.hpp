#pragma once

#include <string>
#include <iostream>
#include <cstring>
#include <cinttypes>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <thread>

class Process
{

public:
    Process(const std::string& process_name, pid_t pid = 0);
    bool is_running();

    bool read(uintptr_t address, void* buffer, size_t size);
    bool write(uintptr_t address, void* buffer, size_t size);

private:
    pid_t get_pid(const std::string& process_name);

    pid_t _pid;
};
