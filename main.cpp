#include <iostream>

using namespace std;
string commands() {
    string commands = "\nhelp: gives info about commands\n\tusage: help OR help <command>\n";
    commands += "\nls: prints the contents of a directory\n\tusage: ls OR ls <directory>\n";
    commands += "\npwd: prints the path to the current directory\n\tusage: pwd\n";
    commands += "\ncd: changes the current directory\n\tusage: cd <directory>\n";
    commands += "\nmkdir: creates a new directory\n\tusage: mkdir <name>\n";
    commands += "\nrm: deletes a file\n\tusage:rm [tags] <path to file>\n\t\ttags:\n\t\t\t-r: remove recursively (directory)\n";
    commands += "\nshutdown: shuts down system\n\tusage: shutdown\n\t\tnote: MUST be run as super user\n";

    return commands;
}
string ref(string com) {
    string out;
    if (com == "help") {
        out = "\nhelp: help <command> OR help\n\tLists or give info about commands\n\tUsage: help: list commands\n\tAlternate usage: help <command>: give more detailed info about specific commands.\n";
    } else if (com == "ls") {
        out = "\nls: ls OR ls <path>\n\tLists the contents of a directory\n\tUsage: ls: list contents of the current directory\n\tAlternate usage: ls <patj>: list the contents of a specific directory.\n";
    } else if (com == "pwd") {
        out = "\npwd: pwd\n\tPrints the path to the current directory\n\tUsage: pwd: print the path to the active directory.\n";
    } else if (com == "cd") {
        out = "\ncd: cd <directory> OR cd <path>\n\tChanges the active directory\n\tUsage: cd <directory>: changes the active directory to the specified folder\n\tAlternate usage: cd <path>: changes the active directory to the specified path.\n";
    } else{
        cout << "Unknown command '" << com << "'.\n";
    }
    return out;
}
int main() {
    cout << "Welcome to Cmand\nType in a command or type 'help' to get available commands\n";
    bool run = true;
    string in;
    string dir = "/";
    int lvl = 0;
    string contents[5][6];
    contents[0][0] = "/";
    contents[0][1] = "home";
    contents[1][0] = "/home";
    contents[1][1] = "user";
    while (run) {
        cout << "Cmand $ ";
        getline(cin, in);
        if (in.find("help") != string::npos) {
            if (in == "help") {
                cout << "Cmand basic commands:\n" << commands() << endl;
            } else {
                cout << ref(in.replace(0, 5, ""));
            }
        } else if (in.find("ls") != string::npos) {
            string udir;
            if (in == "ls") {
                udir = dir;
            } else if (in != "ls") {
                udir = in.replace(0, 3, "");
            }
            bool found = false;
            for (int i = 0; i <= 4; i++) {
                if (contents[i][0] == udir) {
                    found = true;
                    for (int t = 1; t <= 5; t++) {
                        if (!contents[i][t].empty()) {
                            cout << contents[i][t] << "\t";
                        }
                    }
                    i = 4;
                    cout << "\n";
                }
            }
            if (!found) {
                cout << "directory not found\n";
            }
        } else if (in == "pwd") {
            cout << dir << endl;
        } else if (in.find("cd") != string::npos) {
            string cdir = in.replace(0, 3, "");
            if (cdir == "..") {
                lvl--;
                dir = contents[lvl][0];
            } else if (in[0] == '/') {
                for (int i = 0; i <= 4; i++) {
                    if (contents[i][0] == cdir) {
                        dir = cdir;
                        lvl = i;
                    }
                }
            } else if (in[0] != '/') {
                for (int i = 1; i <= 5; i++) {
                    if (contents[lvl][i] == cdir) {
                        dir = "/" + cdir;
                        lvl++;
                    }
                }
            }
        } else if (in.find("mkdir") != string::npos) {
            string ndir = in.replace(0,5,"");
            for (int i = 1; i<=5; i++) {
                if (contents[lvl][i].empty()) {
                    contents[lvl][i] = ndir;
                    string path = contents[lvl-1][0]+"/"+ndir;
                    for (int f = lvl+1;f <= 4; f++) {
                        if (contents[f][0].empty()) {
                            contents[f][0] = path;
                        }
                    }
                    break;
                }
            }
        } else if (in.find("shutdown") != string::npos) {
            if (in.find("sudo") != string::npos) {
                cout << "Shutting down . . .";
                run = false;
            } else {
                cout << "Command 'shutdown' must be run as root\n";
            }
        } else {
            cout << "Unknown command '" << in << "'. Use 'help' to display commands\n";
        }
    }
}