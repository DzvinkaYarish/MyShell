//
// Created by dzvinka on 08.04.17.
//

#include "innerCommands.h"
#include "sh_tools.h"

int cd(std::vector<std::string> args)
{
    ///cd - home dir
/// cd ~ - home dir
/// cd .. - one dir up


    if (displayHelp(args)) {
        return 0;
    }

    if (args.size() == 1 || args[1] == "~")
    {
        chdir(getenv("HOME"));
        return 0;
    } else if (args[1] == "..")
    {
		chdir(args[1].data());
		return 0;
#if 0		
        //! boost::filesystem::path currentDir  = get_current_dir_name();
		//! УВАГА! 1. get_current_dir_name() -- нестандартна.
		//! 	   2. Пам'ять вона виділяє malloc(), а після того, що Ви
		//!				зробили, її ніяк не звільниш -- memory leak.
        boost::filesystem::path currentDir{ my_get_current_dir_name() };
        std::vector<std::string> splitVec;
        std::string oneDirUp;
        boost::split(splitVec, currentDir.string(), boost::is_any_of("/"), boost::token_compress_on);
		//! У вихідному варіанті -- на моїй системі висло...
		//! Anyway, boost та chdir() розуміють ".." -- можна було не ускладнювати собі життя.
		//! Працює завдяки тому, що в кожній директорії є директорія-backlink, з іменем "..".
		//! Див. також http://www.boost.org/doc/libs/1_51_0/libs/filesystem/doc/reference.html#canonical
        for (int i = 0; i < splitVec.size() - 1; i++) {
            oneDirUp += splitVec[i];
            oneDirUp += "/";
        }
        chdir(oneDirUp.c_str());
        // currentDir = my_get_current_dir_name();
        return 0;
#endif		
    } else if (args[1] == "/")
    {
        chdir("/");
        return 0;
    } else
    {
        std::string dir = args[1];
        dir.erase(std::remove(dir.begin(), dir.end(), '\n'), dir.end());
        chdir(dir.c_str());

        if (!errno){
            return 0;
        }
        std::cout << "cd: "<< strerror(errno) << std::endl;
        errno = 0;
    }

    return -1;


}

int pwd(std::vector<std::string> args)
{
    if (displayHelp(args)) {
        return 0;
    }

    if (args.size() == 1)
    {
        std::cout << boost::filesystem::current_path().string() << std::endl;
    } else
    {
        std::cout << "pwd: invalid option " + args[1] << std::endl;
    }
    return 0;
}

bool displayHelp(std::vector<std::string> args)
{
    std::map<std::string, std::string> helpMap;
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
            "                        extension -X, size -S, time -t\n"
            "-r, --reverse           reverse order while sorting\n"
            "-help                   display this help and exit";
    helpMap["mkdir"] = "Usage: mkdir [OPTION]... DIRECTORY...\n"
            "Create the DIRECTORY(ies), if they do not already exist.\n"
            "-h, --help     display this help and exit";
    helpMap["cp"] =  "Usage: cp [OPTION]...  SOURCE DEST\n"
            "  or:  cp [OPTION]... SOURCE... DIRECTORY\n"
            "Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY."
            "-f,       do not prompt before overwriting\n"
            " -h, -help     display this help and exit";
    helpMap["mv"] = "Usage: mv [OPTION]... SOURCE DEST\n"
            "  or:  mv [OPTION]... SOURCE... DIRECTORY\n"
            "Rename SOURCE to DEST, or move SOURCE(s) to DIRECTORY.\n"
            "-f,       do not prompt before overwriting\n"
            " -h, -help     display this help and exit";
    helpMap["rm"] = "Usage: rm [OPTION]... FILES...\n"
            "Remove (unlink) the FILE(s).\n"
            " -f,           ignore nonexistent files and arguments, never prompt\n"
            " -R   remove directories and their contents recursively\n"
            " -h, --help     display this help and exit";


    if (find(args.begin(), args.end(), "-h") != args.end() || find(args.begin(), args.end(), "--help") != args.end())
    {
        std::cout << helpMap[args[0]] << std::endl;
        return true;
    }
    return false;
}

