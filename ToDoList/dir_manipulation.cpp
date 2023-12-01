#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string_view>
#include <filesystem>
#include <sstream>
#include <vector>
#include <windows.h>
#include <locale>
#include <codecvt>

namespace fs = std::filesystem;

#include "sharedVars.h"
#include "funcPrototypes.h"

void change_dir(std::string new_path) {
    if (new_path == "...") {
        size_t lastSlashPos = path.find_last_of('/');
        if (lastSlashPos != std::string::npos) {
            path = path.substr(0, lastSlashPos);
        }
    }
    else if (fs::is_directory(path + "/" + new_path)) {
        path = path + "/" + new_path;
    }
    else if (fs::is_directory(new_path)) {
        path = new_path;
    }
    else {
        std::cout << new_path << " is not a valid directory\n";
    }
}

void create_directory(std::string dirpath) {
    dirpath = path + "/" + dirpath;
    try {
        fs::create_directory(dirpath);
        std::cout << "Created directory: " << dirpath << "\n";
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}