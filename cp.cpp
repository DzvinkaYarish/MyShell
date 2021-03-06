#include <iostream>
#include <cstring>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::filesystem;

boost::filesystem::path concat(boost::filesystem::path pp, char c[])
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

    if (argc < 3)
    {
        std::cout << "cp: missing operand" << std::endl;
        return  -1;
    }
    errno = 0;
    string userInput;
    bool f = false;

    int indxoff = -1;
    for (int i  = 0; i < argc; i++) {
        if ((strcmp(argv[i], "-h") == 0 ||strcmp(argv[i], "--help") == 0)) 
        {
            cout << "Usage: cp [OPTION]...  SOURCE DEST\n"
                    "  or:  cp [OPTION]... SOURCE... DIRECTORY\n"
                    "Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY."
                    "-f,       do not prompt before overwriting\n"
                    " -h, -help     display this help and exit" << endl;
            return 0;
        }
        else if (strcmp(argv[i], "-f") == 0) {
            f = true;
            indxoff = i;
            break;
        }
    }

    boost::filesystem::path fullpath;
    int indxoffdir;
    if (indxoff < argc - 1)
    {
        indxoffdir = argc - 1;
    } else
    {
        indxoffdir = argc - 2;
    }

    if (!boost::algorithm::starts_with(argv[indxoffdir], "/") )
    {
        fullpath = concat(boost::filesystem::current_path(), argv[indxoffdir]);
    } else {
        fullpath = argv[indxoffdir];
    }

    if (is_directory(fullpath))
    {
        for (int i = 1; i < argc - 1; i++)
        {
            if (i == indxoff || i == indxoffdir)
            {
                continue;
            }

            vector<string> splitVec;
            boost::split(splitVec, argv[i], boost::is_any_of("/"), boost::token_compress_on);
            string newName = fullpath.string() + '/' + splitVec[splitVec.size() - 1];
            //cout << newName << endl;
            if (!f && boost::filesystem::exists(newName)) {

                cout << "Do you want to replace " << argv[i] << "?y/n" << endl;
                getline(cin, userInput);
                if (userInput == "y") {
                    errno = 0;
                    try {
                        copy_file(argv[i], newName.c_str(), copy_option::overwrite_if_exists);
                    } catch (boost::filesystem::filesystem_error){
                        cout << "cp: no such file or directory" << endl;
                        continue;
                    }
                }
            } else
            {
                errno = 0;
                try {
                    copy_file(argv[i], newName.c_str(), copy_option::overwrite_if_exists);
                }  catch (boost::filesystem::filesystem_error){
                    cout << "cp: no such file or directory" << endl;
                    continue;
                }
            }
            if (!errno) {
                //cout << "no error in mv" << endl;
                continue;
            } else {
                cout << "cp: " << strerror(errno) << endl;
                errno = 0;
                continue;
            }
        }
    } else if (argc < 5) {
        int indxofsrc;
        int indxofdest;
        if (indxoff == 1) {
            indxofsrc = 2;
            indxofdest = 3;

        } else if (indxoff == 2) {
            indxofsrc = 1;
            indxofdest = 3;
        } else
        {
            indxofsrc = 1;
            indxofdest = 2;
        }

        if (!boost::algorithm::starts_with(argv[indxofdest], "/") )
        {
            fullpath = concat(boost::filesystem::current_path(), argv[indxofdest]);
        } else {
            fullpath = argv[indxofdest];
        }


        if (!f && exists(fullpath)) {
            cout << "Do you want to replace " << argv[2] << "?y/n" << endl;
            getline(cin, userInput);
            if (userInput == "y") {
                errno = 0;
                try {
                    copy_file(argv[indxofsrc], argv[indxofdest], copy_option::overwrite_if_exists);
                } catch (boost::filesystem::filesystem_error){
                    cout << "cp: no such file or directory" << endl;
                }
            }
        } else {
            errno = 0;
            try {
                copy_file(argv[indxofsrc], argv[indxofdest], copy_option::overwrite_if_exists);
            }  catch (boost::filesystem::filesystem_error){
                cout << "cp: no such file or directory" << endl;
            }

        }
        if (!errno) {
            cout << "no error in mv" << endl;
            return 0;
        } else {
            cout << "cp: " << strerror(errno) << endl;
            errno = 0;
            return -1;
        }

    }
    return 0;
}
