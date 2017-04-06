//
// Created by dzvinka on 06.04.17.
//

#include "cd.h"


//int cd(std::vector<std::string> args)
/////cd - home dir
///// cd ~ - home dir
///// cd .. - one dir up
//{
//    std::string dir = args[1];
//    dir.erase(std::remove(dir.begin(), dir.end(), '\n'), dir.end());
//    if (args.size() == 1 || args[1] == "~")
//    {
//        chdir(getenv("HOME"));
//        //boost::filesystem::path currentDir = getenv("HOME");
//        return 0;
//    } else if (args[1] == "..")
//    {
//        boost::filesystem::path currentDir  = get_current_dir_name();
//        std::vector<std::string> splitVec;
//        std::string oneDirUp;
//        boost::split(splitVec, currentDir.string(), boost::is_any_of("/"), boost::token_compress_on);
//        for (int i = 0; i < splitVec.size() - 1; i++) {
//            oneDirUp += "/";
//            oneDirUp += splitVec[i];
//        }
//        chdir(oneDirUp.c_str());
//       // cout << oneDirUp << endl;
//        currentDir = get_current_dir_name();
//        return 0;
//    } else if (args[1] == "/")
//    {
//        chdir("/");
//        //currentDir = get_current_dir_name();
//        return 0;
//    } else if (args[1] == "-h" || args[1] == "--help")
//    {
//        std::cout << "Change to the DIRECTORY if exists\n"
//                "~, [space]    change to the home directory\n"
//                "..            go one directory up\n"
//                "-h, --help    display this help" << std::endl;
//    } else
//    {
//        chdir(dir.c_str());
//
//        if (!errno){
//            //currentDir = get_current_dir_name();
//            return 0;
//        }
//        std::cout << "cd: "<< strerror(errno) << std::endl;
//        errno = 0;
//    }
//
//    return -1;
//}
