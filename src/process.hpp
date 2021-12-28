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
    bool find_fov_address(uintptr_t fov_address, uintptr_t fov_offset);
    bool set_fov(float fov);
    float get_fov();
    bool is_running();
private:
    pid_t get_pid(const std::string& process_name);
    
    bool read(uintptr_t address, void* buffer, size_t size);
    bool write(uintptr_t address, void* buffer, size_t size);

    pid_t _pid;
    uint32_t _fov_address;
};

Process::Process(const std::string& process_name, pid_t pid) :
    _pid(-1), _fov_address(0)
{
    while ((_pid = get_pid(process_name)) == -1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

bool Process::find_fov_address(uintptr_t fov_address, uintptr_t fov_offset)
{
    uint32_t ptr;
    if (!read(fov_address, (void*)&ptr, sizeof(ptr)))
    {
        return false;
    }

    _fov_address = ptr + fov_offset;
    return true;
}

bool Process::set_fov(float fov)
{
    return write(_fov_address, (void*)&fov, sizeof(fov));
}

float Process::get_fov()
{
    float fov;
    if (!read(_fov_address, (void*)&fov, sizeof(fov)))
    {
        return 0.f;
    }
    
    return fov;
}

pid_t Process::get_pid(const std::string& process_name)
{
    FILE *cmd = popen(std::string("pidof ").append(process_name).c_str(), "r");
    char line[20];
    memset(line, '0', 20);
    fgets(line, 19, cmd);
    pid_t pid = strtoul(line, NULL, 10);
    pclose(cmd);
    if (!pid)
        pid = -1;
    return pid;
}

bool Process::is_running()
{
    if (_pid == -1)
        return false;
    struct stat sts;
    return !(stat(("/proc/" + std::to_string(_pid)).c_str(), &sts) == -1 && errno == ENOENT);
}

bool Process::read(uintptr_t address, void* buffer, size_t size)
{
    if (_pid == -1)
        return false;

    iovec local[1];
    iovec remote[1];

    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = (void*)address;
    remote[0].iov_len = size;

    return (process_vm_readv(_pid, local, 1, remote, 1, 0) == size);
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