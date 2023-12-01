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

void create_file(const std::string fname) {
    std::ofstream file(path + "/" + fname);

    if (file.is_open()) {
        std::cout << "File " << fname << " was created\n";
        file.close();
    }
    else {
        std::cout << "File was unable to create\n";
    }
}

void list_files(std::string input) {
    if (input == "ls" || input == "ls -d" || input == "ls -f" || input == "ls -?") {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (fs::is_directory(entry.path())) {
                if (input == "ls" || input == "ls -d") {
                    std::cout << "Directory: " << entry.path().filename() << '\n';
                }
            }
            else if (fs::is_regular_file(entry.path())) {
                if (input == "ls" || input == "ls -f") {
                    std::cout << "File: " << entry.path().filename() << '\n';
                }
            }
            else {
                if (input == "ls" || input == "ls -?") {
                    std::cout << "Other type: " << entry.path().filename() << '\n';
                }
            }
        }
    }
    else {
        std::cout << input << " is incorrect format\n";
    }
}

void move_file(std::string sourcePath, std::string destinationPath, std::string shortcut) {
    if (shortcut == "-s") { sourcePath = path + "/" + sourcePath; }
    else if (shortcut == "-d") { destinationPath = path + "/" + destinationPath; }
    else if (shortcut == "-b")
    {
        sourcePath = path + "/" + sourcePath;
        destinationPath = path + "/" + destinationPath;
    }

    size_t found = sourcePath.find_last_of("/"); // Find the last occurrence of '/'
    std::string sourceFileName;

    if (found != std::string::npos) { // Check if '/' was found
        sourceFileName = sourcePath.substr(found + 1); // Get the substring starting after the last '/'
    }

    destinationPath = destinationPath + "/" + sourceFileName;

    try {
        fs::rename(sourcePath, destinationPath);
        std::cout << "File moved successfully";
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void open_file(const std::string fname) {
    std::wstring Wfname = stringToWideString(fname);
    std::wstring Wpath = stringToWideString(path);
    std::wstring fullPath = Wpath + L"/" + Wfname;
    ShellExecuteW(NULL, L"open", fullPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
}