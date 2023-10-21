#include "process.hpp"
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdint>
#include <cerrno>
#include <cstring>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Function to check the validity of an address in a process
bool isAddressValid(pid_t pid, uintptr_t address) {
    std::ifstream mapsFile("/proc/" + std::to_string(pid) + "/maps");
    if (!mapsFile.is_open()) {
        std::cerr << "Failed to open /proc/[PID]/maps" << std::endl;
        return false; // Couldn't open the memory map
    }

    std::string line;
    while (std::getline(mapsFile, line)) {
        std::istringstream iss(line);
        uintptr_t start, end;
        iss >> std::hex >> start;
        iss.ignore(1); // Skip the '-' character
        iss >> std::hex >> end;

        if (address >= start && address < end) {
            return true; // Address is within a valid memory region
        }
    }

    return false; // Address is not within any valid memory region
}

Process::Process(const std::string& process_name, pid_t _pid) :
    _pid(-1)
{
    std::cout << "Waiting for game (" + process_name + ") to start\n";
    while ((_pid = get_pid(process_name)) == -1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Game found\n";
}

pid_t Process::get_pid(const std::string& process_name)
{
    std::string process = std::string("pidof ") + process_name;
    FILE *cmd = popen(process.c_str(), "r");
    char line[20];
    memset(line, '0', 20);
    fgets(line, 19, cmd);
    pid_t pid = strtoul(line, NULL, 10);
    pclose(cmd);
    if (!pid)
        _pid = -1;
    _pid = pid;
    return pid;
}

bool Process::is_running()
{
    if (_pid == -1)
        return false;

    struct stat sts{};
    return !(stat(("/proc/" + std::to_string(_pid)).c_str(), &sts) == -1 && errno == ENOENT);
}

bool Process::read(uintptr_t address, void* buffer, size_t size)
{
    if (_pid == -1)
        return false;

    iovec local[1]{};
    iovec remote[1]{};

    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = (void*)address;
    remote[0].iov_len = size;

    const auto result = process_vm_readv(_pid, local, 1, remote, 1, 0);
    return ( result == size);
}

bool Process::write(uintptr_t address, void* buffer, size_t size)
{
    if (_pid == -1)
        return false;

    iovec local[1];
    iovec remote[1];

    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = (void*)address;
    remote[0].iov_len = size;

    return (process_vm_writev(_pid, local, 1, remote, 1, 0) == size);
}
