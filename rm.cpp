//
// Created by dzvinka on 31.03.17.
//


#include <iostream>
#include <cstring>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;
int main(int argc, char *argv[])
{
    string userInput;
    for (int i = 2; i < argc; i++) {
        if (is_directory((path)argv[i]) && argv[1] == "false")
        {
            continue;
        }
        if (argv[0] == "false")
        {
            cout << "Do you want to delete " << argv[i] << "?y/n"<< endl;
            getline(cin, userInput);
            if (userInput == "y")
            {
                remove(argv[i]);
            }
        } else {
            remove(argv[i]);
        }
        if (!errno) {
            cout << "no error in rm" << endl;
            continue;
        } else {
            cout << "rm: " << strerror(errno) << endl;
            errno = 0;
            continue;

        }
    }
    return 0;
}




