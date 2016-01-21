#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>

enum ROY_SYSTEM { _PATH_MAX = 1024};
// _PATH_MAX , the leading underscore is used to avoid conflict with stdlib Macro

namespace roy_c {
    ROY_SYSTEM pth_max = _PATH_MAX;
    // Initialize all constants and configuration information at the begining
    // _PATH_MAX: define the length of the buffer

    /*
     * Mirrored Python String Join Method.
     */
    std::string str_join(std::vector<std::string> strs, std::string separator) {
        std::string joined_str = "";
        for(int i=0;i<strs.size();++i){
            joined_str += strs[i] + separator;
        }
        joined_str.erase(joined_str.length()-separator.length()
                , separator.length());
        return joined_str;
    }

    pid_t get_pid() {
        pid_t current_pid = getpid();
        return current_pid;
    }


    std::string get_selfpath() {
        char buff[pth_max];
        ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);
        if (len != -1) {
            buff[len] = '\0';
            return std::string(buff);
        }
    }

    std::string get_exe_name() {
        std::string selfpath = get_selfpath();
        std::vector<std::string> strs;
        boost::split(strs, selfpath, boost::is_any_of("/"));
        return strs[strs.size() - 1];
    }

    std::string get_entry_pth() {
        std::string selfpath = get_selfpath();
        std::vector<std::string> strs;
        boost::split(strs, selfpath, boost::is_any_of("/"));
        strs.pop_back();
        // strip last member of vector

        return str_join(strs, "/");
    }

    std::string get_abs_pth(std::string rel_pth){
        std::string entry_pth = get_entry_pth();
        std::string abs_pth = entry_pth + "/" + rel_pth;
        return abs_pth;
    }

}


