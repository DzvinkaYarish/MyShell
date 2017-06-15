//
// Created by dzvinka on 31.03.17.
//

#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{

	//cout << argv[0] << endl;
    if (argc < 2) 
    {
        std::cout << "mkdir: missing operand" << std::endl;
        return -1;
    }
    for (int i = 0; i < argc; i++) 
    {
        if(strcmp(argv[i], "-h") == 0 ||strcmp(argv[i], "--help") == 0) 
        {
            cout << "Usage: mkdir [OPTION]... DIRECTORY...\n"
                    "Create the DIRECTORY(ies), if they do not already exist.\n"
                    "-h, --help     display this help and exit" << endl;
            return 0;
        }
    }
	int res = mkdir(argv[1], S_IRWXU);
    if (!res) {
        //cout << "no error here" << endl;
        return 0;
    } else
    {
        cout << "mkdir: " << strerror(errno) << endl;
		errno = 0;
        return -1;
    }

}
