#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string_view>
#include <sstream>
#include <windows.h>
#include <locale>
#include <codecvt>

#include "funcPrototypes.h"
#include "sharedVars.h"

std::wstring stringToWideString(const std::string& narrowStr) {
    //very zesty code, i totally made this code myself. this is why c < c++ < any other code
    int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, narrowStr.c_str(), -1, NULL, 0);
    wchar_t* wideStr = new wchar_t[wideStrLen];
    MultiByteToWideChar(CP_UTF8, 0, narrowStr.c_str(), -1, wideStr, wideStrLen);
    std::wstring result(wideStr);
    delete[] wideStr;
    return result;
}

std::string defaultPath() { //gets the default path
    char* homePath;
    size_t len;
    errno_t err = _dupenv_s(&homePath, &len, "HOMEPATH");

    std::string homePathSTR;
    if (err == 0 && homePath != nullptr) {
        homePathSTR.assign(homePath);
        free(homePath); // free allocated memory
    }
    else {
        std::cout << "Default CMD Path not found." << std::endl;
        running = false;
        return "null";
    }
    homePathSTR = "C:" + homePathSTR;

    for (int i = 0; i < homePathSTR.length(); i++)
    {
        if (homePathSTR[i] == '\\') {
            homePathSTR[i] = '/';
        }
    }

    return homePathSTR;
}

void show_help() {
    std::cout << "If has [] means a parameter and {} means optional parameter!!!\n\n";
    std::cout << "help or hp --- shows the help screen\n\n";
    std::cout << "ex --- exits\n\n";
    std::cout << "ls [specifier] --- shows the files in selected directory\n* [specifier] decides which file type you should only see (-f = files -d = directories -? = other)\n\n";
    std::cout << "cl --- clears the console\n\n";
    std::cout << "cd [directory] --- goes to the [directory] directory\n* if [directory] is ... then it goes to parent directory\n\n";
    std::cout << "cf [file name] --- creates a file with the name [file name]\n* must specify file type in the name\n\n";
    std::cout << "mf [source file] [destination] {shortcut} --- moves a file with the path [source file] (with name) into the directory [destination]\n* Must specify file type in the file name\n* {shortcut} decides which input should have current path added to it (-s = source -d = destination -b = both)\n\n";
    std::cout << "md [directory] --- creates a directory called [directory]\n\n";
    std::cout << "of [file name] --- opens a file named [file name]\n* the file name must include the file type\n\n";
}
