#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>

#define SELF_PATH_MAX 1024

pid_t get_pid() {
    pid_t current_pid = getpid();
    return current_pid;
}

std::string get_selfpath() {
    char buff[SELF_PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1) {
      buff[len] = '\0';
      return std::string(buff);
    }
}
