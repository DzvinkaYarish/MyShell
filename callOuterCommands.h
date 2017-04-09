//
// Created by dzvinka on 08.04.17.
//

#ifndef MYSHELL_CALLOUTERCOMMANDS_H
#define MYSHELL_CALLOUTERCOMMANDS_H
#include <boost/lambda/lambda.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <dirent.h>

#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int callOuter(std::vector<std::string> args);
int startNewProcess(char *  argv[]);





#endif //MYSHELL_CALLOUTERCOMMANDS_H
