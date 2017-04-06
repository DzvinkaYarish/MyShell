#include <boost/lambda/lambda.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <dirent.h>
#include "cd.h"
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
//#include <map>

using namespace boost::filesystem;

using namespace std;   /// BBBBBBBBBBBAAADDDDD

typedef int (* commandToExec)(vector<string> args);
map<string, commandToExec> commandMap;



path currentDir = initial_path();



bool displayHelp(vector<string> args)
{
    map<string, string> helpMap;
    helpMap["pwd"] = "Show current working directory\n"
            "-h, --help    display this help";
    helpMap["cd"] = "Change to the DIRECTORY if exists\n"
            "~, [space]    change to the home directory\n"
            "..            go one directory up\n"
            "-h, --help    display this help";
    helpMap["ls"] = "Usage: ls [OPTION]... [PATH|MASK]...\n"
            "List information about the FILEs (the current directory by default).\n"
            "Sort entries alphabetically if --sort is not specified.\n"
            "-l                      use a long listing format\n"
            " --sort=WORD            sort by WORD instead of name: none -U,\n"
            "                             extension -X, size -S, time -t\n";
    if (find(args.begin(), args.end(), "-h") != args.end()  || find(args.begin(), args.end(), "--h") != args.end())
    {
        return true;
    }
    return false;
}

int executeCommand(commandToExec commnd, vector<string> args)
{
    return commnd(args);

}
int callCP(vector<string> args) {

    if (displayHelp(args))
    {
        cout << "Usage: cp [OPTION]...  SOURCE DEST\n"
                "  or:  cp [OPTION]... SOURCE... DIRECTORY\n"
                "Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY."
                "-f,       do not prompt before overwriting\n"
                " -h, -help     display this help and exit" << endl;


    }
    if (args.size() < 4) {
        cout << "cp: missing operand" << endl;
        return -1;
    } else if (args.size() > 10) {
        cout << "cp: too many operands" << endl;
        return -1;
    }
    char * const argv[10]={(char *)malloc(256), (char *)malloc(256), (char *)malloc(256),(char *)malloc(256),
                           (char *)malloc(256), (char *)malloc(256), (char *)malloc(256), (char *)malloc(256),
                           (char *)malloc(256), (char *)malloc(256),};


    if (find(args.begin(), args.end(), "f") != args.end() )
    {
        strcpy(argv[0], "f");
    } else
    {
        strcpy(argv[0], "false");
    }

    int count = 1;
    for (int i = 0; i < args.size(); i++)
    {
        if (args[i] != "f") {
            strcpy(argv[count], args[i].c_str());
            count++;
        }
    }
    pid_t childPid;
    childPid = fork();
    if (childPid == 0)
    {
        execvp("home/dzvinka/CLionProjects/MyShell/cp",  argv);
        cout << strerror(errno) << endl;
    } else if (childPid < 0)
    {
        return -1;
    }
    return 0 ;
}

int callMV(vector<string> args)
{
    if (displayHelp(args))
        {
            cout << "Usage: mv [OPTION]... SOURCE DEST\n"
                    "  or:  mv [OPTION]... SOURCE... DIRECTORY\n"
                    "Rename SOURCE to DEST, or move SOURCE(s) to DIRECTORY.\n"
                    "-f,       do not prompt before overwriting\n"
                    " -h, -help     display this help and exit" << endl;


    }
    if (args.size() < 4) {
        cout << "mv: missing operand" << endl;
        return -1;
    } else if (args.size() > 10) {
        cout << "mv: too many operands" << endl;
        return -1;
    }
    char * const argv[10]={(char *)malloc(256), (char *)malloc(256), (char *)malloc(256),(char *)malloc(256),
                           (char *)malloc(256), (char *)malloc(256), (char *)malloc(256), (char *)malloc(256),
                           (char *)malloc(256), (char *)malloc(256),};


    if (find(args.begin(), args.end(), "f") != args.end() )
    {
        strcpy(argv[0], "f");
    } else
    {
        strcpy(argv[0], "false");
    }

    int count = 1;
    for (int i = 0; i < args.size(); i++)
    {
        if (args[i] != "f") {
            strcpy(argv[count], args[i].c_str());
            count++;
        }
    }
    pid_t childPid;
    childPid = fork();
    if (childPid == 0)
    {
        execvp("home/dzvinka/CLionProjects/MyShell/mv",  argv);
        cout << strerror(errno) << endl;
    } else if (childPid < 0)
    {
        return -1;
    }
    return 0 ;
}



int callRM(vector<string> args)
{
    //argv[0] -[f]
    //argv[1] - [R]

    if (displayHelp(args))
    {
        cout << "Usage: rm [OPTION]... FILES...\n"
                "Remove (unlink) the FILE(s).\n"
                " -f,           ignore nonexistent files and arguments, never prompt\n"
                " -R   remove directories and their contents recursively\n"
                " -h, --help     display this help and exit" << endl;


    }
    if (args.size() < 3) {
        cout << "rm: missing operand" << endl;
        return -1;
    } else if (args.size() > 10) {
        cout << "rm: too many operands" << endl;
        return -1;
    }
    char * const argv[10]={(char *)malloc(256), (char *)malloc(256), (char *)malloc(256),(char *)malloc(256),
                           (char *)malloc(256), (char *)malloc(256), (char *)malloc(256), (char *)malloc(256),
                           (char *)malloc(256), (char *)malloc(256),};


    if (find(args.begin(), args.end(), "f") != args.end() )
    {
        strcpy(argv[0], "f");
    } else
    {
        strcpy(argv[0], "false");
    }
    if (find(args.begin(), args.end(), "R") != args.end() )
    {
        strcpy(argv[1], "R");
    } else
    {
        strcpy(argv[1], "false");
    }
    int count = 2;
    for (int i = 0; i < args.size(); i++)
    {
        if (args[i] != "f" && args[i] != "R") {
            strcpy(argv[count], args[i].c_str());
            count++;
        }
    }
    pid_t childPid;
    childPid = fork();
    if (childPid == 0)
    {
        execvp("home/dzvinka/CLionProjects/MyShell/rm",  argv);
        cout << strerror(errno) << endl;
    } else if (childPid < 0)
    {
        return -1;
    }
    return 0 ;
}


int callMKDir(vector<string> args)
{

    if (args.size() < 2) {
        cout << "mkdir: missing operand" << endl;
        return -1;
    }
    if (args[1] == "-h" || args[1] == "--help")
    {
        cout << "Usage: mkdir [OPTION]... DIRECTORY...\n"
                "Create the DIRECTORY(ies), if they do not already exist.\n"
                "-h, --help     display this help and exit" << endl;

    }

//    char * const argv[1]={(char *)malloc(256)};
//    strcpy(argv[0], args[1].c_str());

    vector<const char*> pointers;
    for (int i = 0; i < args.size(); i++)
    {
        pointers.push_back(args[i].c_str());
    }
    pointers.push_back('\0');

    pid_t childPid;
    childPid = fork();
    if (childPid == 0)
    {
        execvp("home/dzvinka/CLionProjects/MyShell/mkdir", const_cast<char * const> (pointers.data()));
        cout << strerror(errno) << endl;
    } else if (childPid < 0)
    {
        return -1;
    }
    return 0 ;
}

int pwd(vector<string> args)
{

    if (args.size() == 1)
    {

        cout << current_path().string() << endl;
    } else if (args[1] == "-h" || args[1] == "--help")
    {
        cout <<"Show current working directory\n"
                "-h, --help    display this help and exit" << endl;
    } else
    {
        cout << "pwd: invalid option -" + args[1] << endl;
    }
    return 0;
}

int cd(vector<string> args)
///cd - home dir
/// cd ~ - home dir
/// cd .. - one dir up
{
    string dir = args[1];
    dir.erase(std::remove(dir.begin(), dir.end(), '\n'), dir.end());
    if (args.size() == 1 || args[1] == "~")
    {
        chdir(getenv("HOME"));
        currentDir = getenv("HOME");
        return 0;
    } else if (args[1] == "..")
    {
        vector<string> splitVec;
        string oneDirUp;
        boost::split(splitVec, currentDir.string(), boost::is_any_of("/"), boost::token_compress_on);
        for (int i = 0; i < splitVec.size() - 1; i++) {
            oneDirUp += "/";
            oneDirUp += splitVec[i];
        }
        chdir(oneDirUp.c_str());
        //cout << oneDirUp << endl;
        currentDir = get_current_dir_name();
        return 0;
    } else if (args[1] == "/")
    {
        chdir("/");
        currentDir = get_current_dir_name();
        return 0;
    } else if (args[1] == "-h" || args[1] == "--help")
    {
       cout << "Change to the DIRECTORY if exists\n"
            "~, [space]    change to the home directory\n"
            "..            go one directory up\n"
               "-h, --help    display this help" << endl;
    } else
    {
        chdir(dir.c_str());

        if (!errno){
           currentDir = get_current_dir_name();
            return 0;
        }
        cout << "cd: "<< strerror(errno) << endl;
        errno = 0;
    }

    return -1;
}




int main()
{
    //commandMap["ls"] = &ls;
    commandMap["cd"] = &cd;
    commandMap["pwd"] = &pwd;

    //commandMap["exit"] = &exit;
    commandMap["mkdir"] = &callMKDir;
    commandMap["rm"] = &callRM;
    commandMap["move"] = &callMV;
    commandMap["cp"] = &callCP;
    string userInput;
    vector<string> splitVec;
    while (1) {
        cout << currentDir.string() << "$ ";
        getline(cin, userInput);

        boost::split(splitVec, userInput, boost::is_any_of(" "), boost::token_compress_on);
        if (splitVec[0] == "exit") {
            break;
        } else {
            if (commandMap.find(splitVec[0]) != commandMap.end()) {

                executeCommand(commandMap[splitVec[0]], splitVec);
            } else {
                cout << splitVec[0] << ": command not found" << endl;
            }
        }
    }
    return 0;
}



