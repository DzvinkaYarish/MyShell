//
// Created by dzvinka on 06.04.17.
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
using namespace boost::filesystem;
struct  fileinfo
{
    const char * name;
    time_t  lastmod;
    uintmax_t size;
    string extens;
    string is_dir;

};
typedef bool (* cmpFunc)(const fileinfo &a, const fileinfo &b);
map<string, cmpFunc> cmpMap;

bool cmpName(const fileinfo &a, const fileinfo &b) {
    if (strcmp(a.name, b.name) < 0) {
        return true;
    }

    return false;
}

bool cmpSize(const fileinfo &a, const fileinfo &b)
{
    return (a.size < b.size);
}

bool cmpDate(const fileinfo &a, const fileinfo &b)
{
    return (a.lastmod < b.lastmod);
}
bool cmpNothing(const fileinfo &a, const fileinfo &b)
{
    return true;
}
bool cmpExtens(const fileinfo &a, const fileinfo &b)
{
    return (a.extens < b.extens);
}

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
    cmpMap["sort=N"] = &cmpName;
    cmpMap["sort=S"] = &cmpSize;
    cmpMap["sort=t"] = &cmpDate;
    cmpMap["sort=U"] = &cmpNothing;
    cmpMap["sort=X"] = &cmpExtens;

    bool l = false;
    bool r = false;
    bool redirect = false;
    vector<string> redirctOptions;
    string sortm = "sort=N";
    string charmask("*");


    path p = "./";
    path curpth = current_path();
    for (int i = 1; i < argc; i++)
    {
        string curarg(argv[i]);
        if (strcmp(argv[i], "-l") == 0)
        {
            l = true;
        } else if (strcmp(argv[i], "-r") == 0)
        {
            r = true;
        } else if (boost::algorithm::starts_with(argv[i], "sort"))
        {
            sortm = argv[i];
        } else if (boost::algorithm::starts_with(argv[i], "/"))
        {
            p = (path)argv[i];
            curpth = p;
            cout << p << endl;
        } else if (curarg.find("<") != -1)
        {
            redirect = true;
            if (curarg.size() < 3)
            {
                curarg += string(argv[i + 1]);
            }
            redirctOptions.push_back(curarg);
        } else
        {
            charmask = argv[i];

        }
    }


    vector<fileinfo> filenames;


    DIR *dpdf;
    struct dirent *epdf;
    cout << "myls1" << endl;
    dpdf = opendir(p.c_str());
    if (dpdf != NULL){
        while (epdf = readdir(dpdf)){
            fileinfo temp;
            vector<string> splitVec;

            if (strcmp(epdf->d_name,".") != 0 && strcmp(epdf->d_name,"..") != 0)
            {
                //cout << epdf->d_name << endl;
                path fullpath = concat(curpth, epdf->d_name);
                temp.name = epdf->d_name;

                try {
                    temp.size = file_size(fullpath);
                    temp.lastmod = last_write_time(fullpath);
                } catch (boost::filesystem::filesystem_error)
                {
                    //cout << "error" << endl;
                    temp.is_dir = "/";
                    temp.size = 0;
                    temp.extens = "dir";
                    filenames.push_back(temp);
                    continue;
                }

                split(splitVec, epdf->d_name, boost::is_any_of("."), boost::token_compress_on);
                temp.extens = splitVec[1];
                temp.is_dir = "";
                filenames.push_back(temp);

            }
        }
    }

    sort(filenames.begin(), filenames.end(), cmpMap[sortm]);
    if (r) {
        reverse(filenames.begin(), filenames.end());
    }
    if (redirect)
    {

        

    }
    basic_regex<char> mask = regex(charmask);
    for (int i = 0; i < filenames.size();i++) {

        if (strcmp(charmask.c_str(), "*") != 0) {
            string s(filenames[i].name);
            //cout <<"s: "<< s << endl;
            if (regex_match(s, mask)) {
                if (l) {
                    cout << filenames[i].is_dir << filenames[i].name << "  " << filenames[i].size << " bytes  " << ctime(&filenames[i].lastmod)
                         << endl;
                } else {

                    cout << filenames[i].is_dir << filenames[i].name << endl;
                }
            }
        } else {
            if (l) {
                cout << filenames[i].is_dir << filenames[i].name << "  " << filenames[i].size << " bytes  " << ctime(&filenames[i].lastmod) << endl;
            } else {
                cout << filenames[i].is_dir << filenames[i].name << endl;
            }
        }
    }

    return 0;
}







