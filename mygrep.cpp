//
// Created by dzvinka on 12.06.17.
//

#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <regex>
#include <fcntl.h>


using namespace std;

vector<string> readFromFile(string filename)
{
    vector<string> strToProcess;
    if (!(boost::algorithm::starts_with(filename, "/"))) {
        filename = boost::filesystem::current_path().string() + "/" + filename;

    }
    fstream fin(filename); //full path to the file
    if (!fin.is_open()) {
        cout << "error reading from file" << endl;
        return strToProcess;
    }

    string line;
    while (getline(fin, line)) {
        string word;
        std::istringstream iss(line);
        while (iss >> word) {
            strToProcess.push_back(word);
        }
    }
    fin.close();
    return strToProcess;
}



int main(int argc, char *argv[]) {

    
    bool v = false;
    bool i = false;
    bool redirect_o = false;
    bool help = false;
    bool pipe = false;

    int fd = -1;

    string redirect_i = "";
    string toMatch = "";

    vector<string >redirectOptions, optionsFromFile, strToProcess;

    std::string filename = "";
    for (int j = 1; j < argc; j++) {
        std::string curarg(argv[j]);

        if (strcmp(argv[j], "-v") == 0) {
            v = true;
        } else if (strcmp(argv[j], "pipe") == 0) {
            pipe = true;

        } else if (strcmp(argv[j], "-i") == 0) {
            i = true;

        }else if ((strcmp(argv[j], "-h") == 0) || (strcmp(argv[j], "--help") == 0))
        {
            help = true;
        }else if (boost::algorithm::starts_with(argv[j], "--file")) {
            vector<string> splitVec;
            std::string arg(argv[j]);
            boost::split(splitVec, arg, boost::is_any_of("="), boost::token_compress_on);
            filename = splitVec[1];
        } else if (curarg.find(">") != -1) {
            redirect_o = true;
            if (curarg.size() < 3) {
                curarg += " " + string(argv[j + 1]);
                j++;
            }
            redirectOptions.push_back(curarg);
        } else if (curarg.find("<") != -1)
        {
            redirect_i = string(argv[j + 1]);
            j++;
        }
        else
        {
            if(toMatch.empty()) {
                toMatch = curarg;
            } else
            {
                strToProcess.push_back(curarg);
            }
        }
    }
    if (help)
    {
        cout << "Usage: grep [OPTION]... PATTERN [FILE]...\n"
        "Search for PATTERN in FILE or standard input.\n"
        "PATTERN is, by default, a string.\n"
        "Example: grep -i 'hello world' main.c\n"
                "Options: \n"
             "-i, --ignore-case         ignore case distinctions\n"
             "-v, --invert-match        select non-matching lines\n"
             "--filename=               specify file to read from\n"
             "-h, --help                 display this help and exit" << endl;
        return 0;
    }
    if (!redirect_i.empty()) {
        optionsFromFile = readFromFile(redirect_i);

        for (string opt: optionsFromFile) {
            if (strcmp(opt.c_str(), "-v") == 0) {
                v = true;
            } else if (strcmp(opt.c_str(), "-i") == 0) {
                i = true;

            }
            else if (boost::algorithm::starts_with(opt.c_str(), "--file")) {
                vector<string> splitVec;
                boost::split(splitVec, opt, boost::is_any_of("="), boost::token_compress_on);
                filename = splitVec[1];
            }else
            {
                if(toMatch.empty()) {
                    toMatch = opt;
                } else
                {
                    strToProcess.push_back(opt);
                }
            }
        }
    }


    if (!filename.empty()) {
        vector<string> temp = readFromFile(filename);
        strToProcess.insert(strToProcess.end(), temp.begin(), temp.end());
    }

    //get possible strings from stdin

    if (pipe) {
        char readbuffer[1000];
        int nbytes = read(0, readbuffer, sizeof(readbuffer));
        readbuffer[998] = '\n';
        string fromPipe(readbuffer);
        std::istringstream iss(fromPipe);
        string word;
        while (iss >> word) {
            strToProcess.push_back(word);
        }
    }


    if (i) {
        transform(toMatch.begin(), toMatch.end(), toMatch.begin(), ::tolower);
    }
    if (redirect_o)
    {
        for(string redopt: redirectOptions)
        {

            if(redopt.find(" ") != -1)
            {
                vector<string> splitVec;
                boost::split(splitVec, redopt, boost::is_any_of(" "), boost::token_compress_on);
                string tofile = boost::filesystem::current_path().string() + "/" + splitVec[1];
                if ((fd = open(tofile.c_str(), O_RDWR | O_CREAT)) == -1) {
                    cout << "error creating a file: " << strerror(errno) <<endl;
                    return -1;
                }
                if (redopt[0] == '2')
                {
                    if(dup2(fd, 2) == -1)
                    {
                        exit(-1);
                    };


                } else
                {
                    if(dup2(fd, 1) == -1)
                    {
                        exit(-1);
                    };
                }


            } else
            {
                if(redopt[0] == '2')
                {
                    if (dup2(redopt[redopt.size() - 1], 2) == -1)
                    {
                        exit(-1);
                    };
                    //close(redopt[redopt.size() - 1]);
                } else
                {
                    if (dup2(redopt[redopt.size() - 1], 1) == -1)
                    {
                        exit(-1);
                    };
                    //close(redopt[redopt.size() - 1]);
                }
            }
        }
    }

    for(string s: strToProcess)
    {
        string sUpper = s;
        if (i)
        {
            transform(s.begin(), s.end(), s.begin(), ::tolower);

        }
        if (v) {
            if (s.find(toMatch) == string::npos)
                {
                    cout << sUpper << endl;
                }
        } else {

            if (s.find(toMatch) != string::npos)
            {
                cout << sUpper << endl;
            }
        }
    }

    if(fd != -1)
    {
        close(fd);
    }
    return 0;


}

