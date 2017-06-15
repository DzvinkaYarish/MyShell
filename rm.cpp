//
// Created by dzvinka on 31.03.17.
//


#include <iostream>
#include <cstring>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

path concat(path pp, char c[])
{
    pp += "/";
    for (int i = 0; i < strlen(c); i++)
    {
        pp += c[i];
    }
    return pp;
}

int main(int argc, char *argv[])
{

    if (argc < 2) 
    {
        std::cout << "rm: missing operand" << std::endl;
        return  -1;
    }
    bool f = false;
    bool R = false;

    for (int i  = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0)
        {
            f = true;
        } else if (strcmp(argv[i], "-R") == 0)
        {
            R = true;

        } else if (strcmp(argv[i], "-h") == 0 ||strcmp(argv[i], "--help") == 0) 
        {
            cout << "Usage: rm [OPTION]... FILES...\n"
                    "Remove (unlink) the FILE(s).\n"
                    " -f,           ignore nonexistent files and arguments, never prompt\n"
                    " -R   remove directories and their contents recursively\n"
                    " -h, --help     display this help and exit" << endl;
            return 0;

        }
    }



    for (int i = 1; i < argc; i++) {
        string userInput;
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "-R") == 0)
       {
           continue;
       }

        if (is_directory((path)argv[i]) && !R)
        {
            cout << "Is a directory" << endl;
            continue;
        }
        if (!f)
        {
            cout << "Do you want to delete " << argv[i] << "?y/n"<< endl;
            getline(cin, userInput);
            if (userInput == "y")
            {
                try {
                    remove_all((path) argv[i]);
                } catch (boost::filesystem::filesystem_error)
                {
                    remove_all(concat(current_path(), argv[i]));
                }
            }
        } else {
            try
            {
            remove(argv[i]);
            } catch (boost::filesystem::filesystem_error)
            {
                remove_all(concat(current_path(), argv[i]));
            }
        }
		//! errno є сенс перевіряти лише зразу після виклику, що повернув помилку.
		//! От так його перевіряти осоливого сенсу немає -- функції не зобов'язані
		//! зануляти errno.
		//! Те ж стосується mkdir
        if (!errno) {
            //cout << "no error in rm" << endl;
            continue;
        } else {
            if(errno != 21)
            cout << "rm: " << strerror(errno) << endl;
            errno = 0;
            continue;
        }
    }
    return 0;
}




