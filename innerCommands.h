//
// Created by dzvinka on 08.04.17.
//

#ifndef MYSHELL_INNERCOMMANDS_H
#define MYSHELL_INNERCOMMANDS_H


#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <map>



int cd(std::vector<std::string> args);
int pwd(std::vector<std::string> args);
int setVariable(std::string name, std::string value, std::map<std::string, std::string> &varMap);
std::string getVariable(std::string name, std::map<std::string, std::string> &varMap);



#endif //MYSHELL_INNERCOMMANDS_H
