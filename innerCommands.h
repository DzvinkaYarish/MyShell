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
bool displayHelp(std::vector<std::string> args);


#endif //MYSHELL_INNERCOMMANDS_H
