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

cout << argv[0] << endl;
mkdir(argv[0], S_IRWXU);
    if (!errno) {
        cout << "no error here" << endl;
        return 0;
    } else
    {
        cout << "mkdir: " << strerror(errno) << endl;
	errno = 0;
        return -1;
    }

}
