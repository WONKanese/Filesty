#include <iostream>

void create_file(const std::string fname); //creates a file with the given name at the selected path

void list_files(std::string input); //lists all files in selected path (input specifies which type)

void move_file(std::string sourcePath, std::string destinationPath, std::string shortcut = "none");

void open_file(const std::string fname);

std::wstring stringToWideString(const std::string& narrowStr);

void change_dir(std::string new_path);

void create_directory(std::string dirpath);

std::string defaultPath();

void show_help();