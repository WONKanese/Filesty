

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

#include "funcPrototypes.h"
#include "sharedVars.h"

namespace fs = std::filesystem;

bool running = true;
std::string path = "";

void read_input(std::string input) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    if (input == "") {
        return;
    }

    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    if (tokens[0] == "ls") {
        list_files(input);
    }
    else if (tokens[0] == "cd") {
        change_dir(input.substr(3));
    }
    else if (input == "ex") {
        running = false;
    }
    else if (tokens[0] == "cf") {
        create_file(tokens[1]);
    }
    else if (tokens[0] == "md") {
        create_directory(tokens[1]);
    }
    else if (tokens[0] == "cl") {
        std::cout << "\033[2J\033[1;1H";
    }
    else if (tokens[0] == "of") {
        if (tokens.size() > 2) 
        {
            open_file(tokens[1], input.substr(4 + tokens[1].length()));
            return;
        }
        open_file(input.substr(3));
        
    }
    else if (tokens[0] == "rd") {
        remove_directory(input.substr(3));
    }
    else if (tokens[0] == "rf") {
        remove_file(tokens[1]);
    }
    else if (tokens[0] == "mf") {
        if (tokens.size() == 4) {
            move_file(tokens[1], tokens[2], tokens[3]);
            return;
        }
        move_file(tokens[1], tokens[2]);
    }
    else if (input == "help" || input == "hp") {
        show_help();
    }
    else {
        std::cout << input << " is not a valid command\n";
    }
}


int main()
{
    path = defaultPath(); 
    std::string input;
    std::cout << "v1 b1\n";
    std::cout << "~~~~~~~~~~~~~~~~~\n";
    std::cout << "~==$ Filesty $==~\n";
    std::cout << "~~~~~~~~~~~~~~~~~\n\n";
    std::cout << "Welcome to ProBigMan21's \nown file manager!\n\nType help for help\n";
    while (running) {
        std::cout << path << "~ ";
        std::getline(std::cin, input);
        read_input(input);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
