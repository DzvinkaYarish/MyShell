#include <iostream>
#include <cstring>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::filesystem;

int main(int argc, char *argv[])
{
    string userInput;
    if (argc == 2) {

        if (argv[0] == "false" && exists(argv[2])) {
            cout << "Do you want to replace " << argv[2] << "?y/n" << endl;
            getline(cin, userInput);
            if (userInput == "y") {
                copy_file((path)argv[1], (path)argv[2]);
            }
        }

        copy_file((path)argv[1], (path)argv[2]);
        if (!errno) {
            cout << "no error in cp" << endl;
            return 0;
        } else {
            cout << "cp: " << strerror(errno) << endl;
            errno = 0;
            return -1;
        }
    } else {
        if (!is_directory((path) argv[argc - 1])) {
            cout << "cp: no such directory" << argv[argc - 1] << endl;

            return -1;
        }
        for (int i = 1; i < argc - 1; i++) {

            vector<string> splitVec;
            boost::split(splitVec, argv[i], boost::is_any_of(" "), boost::token_compress_on);
            string newName = argv[argc - 1] + '/' + splitVec[splitVec.size() - 1];
            if (argv[0] == "false" && exists(argv[i])) {
                cout << "Do you want to replace " << argv[i] << "?y/n" << endl;
                getline(cin, userInput);
                if (userInput == "y") {
                    copy_file((path)argv[i], (path)newName.c_str());
                }
            }
            copy_file((path)argv[i], (path)newName.c_str());
            if (!errno) {
                cout << "no error in cp" << endl;
                continue;
            } else {
                cout << "cp: " << strerror(errno) << endl;
                errno = 0;
                continue;
            }
        }
    }
    return 0;
}
