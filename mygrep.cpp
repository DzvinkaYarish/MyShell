//
// Created by dzvinka on 12.06.17.
//

#include <boost/lambda/lambda.hpp>
#include <dirent.h>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <regex>


using namespace std;
int main(int argc, char *argv[]) {

    cout <<"my grep" << endl;
    if (argc < 3)
    {
        cout << "grep: Missing argument" << endl;
        return -1;
    }

    bool v = false;
    bool i = false;
    bool r = false;
    bool help = false;
    string toMatch = "";

    vector<string >redirectOptions;
    vector<string> strToProcess;
    std::string filename = "";
    for (int j = 1; j < argc; j++) {
        std::string curarg(argv[j]);
        //cout << curarg << endl;
        if (strcmp(argv[j], "-v") == 0) {
            v = true;
        } else if (strcmp(argv[j], "-i") == 0) {
            i = true;

        } else if ((strcmp(argv[j], "-h") == 0) || (strcmp(argv[j], "--help") == 0))
        {
            help = true;
        }else if (boost::algorithm::starts_with(argv[j], "--file")) {
            vector<string> splitVec;
            std::string arg(argv[j]);
            boost::split(splitVec, arg, boost::is_any_of("="), boost::token_compress_on);
            filename = splitVec[1];
        } else if (curarg.find(">") != -1) {
            cout << "redirect" << endl;
            r = true;
            if (curarg.size() < 3) {
                curarg += " " + string(argv[j + 1]);
                j++;
            }
            redirectOptions.push_back(curarg);
        } else
        {
            if(toMatch.empty()) {
                toMatch = curarg;
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

    if (!filename.empty()) {
        fstream fin(filename); //full path to the file
        if (!fin.is_open()) {
            cout << "error reading from file";
            return -1;
        }

        string line;
        while (getline(fin, line)) {
            string word;
            std::istringstream iss(line);
            while (iss >> word) {
                strToProcess.push_back(word);
            }
        }
    }
    for (int j = 1; j < argc; j++)
    {
        if (!boost::algorithm::starts_with(argv[j], "-") && strcmp(argv[j], toMatch.c_str()) != 0)
        {
            strToProcess.push_back(string(argv[j]));
        }
    }
    if (i) {
        transform(toMatch.begin(), toMatch.end(), toMatch.begin(), ::tolower);
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
    return 0;


}

