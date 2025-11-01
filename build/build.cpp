#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <filesystem>

using namespace std;

const vector<string> exclude_dirs = { 
    "lib", 
    "build" 
};
const vector<string> target_file_types = {
    ".cpp",
    ".hpp",
    ".h",
    ".c"
};

bool is_excluded(filesystem::directory_entry file) {
    for (string dir : exclude_dirs)
        if (file.path().filename() == dir)
            return true;
    return false;
}

bool is_target_file(filesystem::directory_entry file) {
    for (string ext : target_file_types)
        if (file.path().extension() == ext)
            return true;
    return false;
}

void find_src(string root, vector<string> &files, string file) {
    for (auto file : filesystem::directory_iterator(file)) {
        string path = file.path().string();

        if (file.is_directory() && !is_excluded(file)) {
            find_src(root, files, path);
        } 
        else if (is_target_file(file)) {
            files.push_back("\"" + path + "\"");
            cout << "<< " << path.replace(0, root.length() + 1, "") << endl;
        }
    }
}

string construct_command(vector<string> files, string target) {
    string command = "g++ -Wall";
    for (string file : files) {
        command += " " + file;
    }
    command += " -o " + target;
    command += " -I ./lib/include -L ./lib/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32";
    return command;
}

int main(int argc, char* argv[]) {
    string current = filesystem::current_path().string();
    vector<string> files;

    find_src(current, files, current);

    string target = argc == 1 ? "unnamed_application" : argv[1];
    string command = construct_command(files, target);
    cout << command << endl;
    system(command.c_str());
    return 0;
}