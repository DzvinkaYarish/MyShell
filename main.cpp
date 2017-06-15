#include <boost/lambda/lambda.hpp>
#include "callOuterCommands.h"
#include "innerCommands.h"
#include "sh_tools.h"
#include <fstream>
#include <iostream>
//#include <map>

//using namespace boost::filesystem;

using namespace std;   /// BBBBBBBBBBBAAADDDDD

typedef int (* commandToExec)(vector<string> args);
map<string, commandToExec> commandMap;
map<string, string> varMap, envVarMap;



int echo(vector<string> args){
    vector<string> splitVec;
    for (int i = 1; i < args.size(); i++) {
        if (boost::algorithm::starts_with(args[i], "$")) {
            //cout << args[i] << endl;
            cout << getVariable(args[i], varMap) << " ";
        } else {
            cout << args[i] << " ";
        }
    }
    cout << endl;
    return 0;

}

int Export(vector<string> args)
{

    vector<string> splitVec;
    if (args[1].find("=") != string::npos)
    {
        boost::split(splitVec, args[1], boost::is_any_of("="), boost::token_compress_on);
        setVariable(splitVec[0], splitVec[1], varMap);
        setVariable(splitVec[0], splitVec[1], envVarMap);
    } else {
        envVarMap[args[1]] = varMap[args[1]];
    }

    return 0;
}

int assign(vector<string> args)
{
    vector<string> splitVec;
    boost::split(splitVec, args[0], boost::is_any_of("="), boost::token_compress_on);
    setVariable(splitVec[0], splitVec[1], varMap);
    return 0;
}



int executeCommand(commandToExec commnd, vector<string> &args)
{
    for (int i = 0; i < args.size(); i++)
    {
        if(boost::algorithm::starts_with(args[i], "$"))
        {
            args[i] = varMap[args[i]];  //put values of variables
        }
    }
    return commnd(args);

}


int readScript(vector<string> args)
{
    fstream fin(args[1]); //full path to the file
    if (!fin.is_open()) {
        cout << "error reading from file";
        return  -1;
    }

    string line;

    while (getline(fin, line)) {
        cout << line << endl;
        vector<string> splitVec, splitVecWithoutComments;
        boost::split(splitVec, line, boost::is_space(), boost::token_compress_on);
        for (string s: splitVec) {
            if (boost::starts_with(s, "#")) {
                break;
            }
            splitVecWithoutComments.push_back(s);
        }
        if(!splitVecWithoutComments.empty()) {
            if (splitVecWithoutComments[0] == "exit") {
                break;
            } else if (commandMap.find(splitVecWithoutComments[0]) != commandMap.end()) {
                executeCommand(commandMap[splitVecWithoutComments[0]], splitVecWithoutComments);
            } else {
                cout << splitVec[0] << ": command not found" << endl;
            }
        }
    }
    return 0;
}



int main()
{
    commandMap["echo"] = &echo;
    commandMap["export"] = &Export;
    commandMap["ls"] = &callOuter;
    commandMap["cd"] = &cd;
    commandMap["pwd"] = &pwd;
    commandMap["grep"] = &callOuter;
    //commandMap["exit"] = &exit;
    commandMap["mkdir"] = &callOuter;
    commandMap["rm"] = &callOuter;
    commandMap["mv"] = &callOuter;
    commandMap["cp"] = &callOuter;
    commandMap["myshell"] = &readScript;
    commandMap["assign"] = &assign;
    commandMap["pipeline"] = &organizePipes;
    string userInput;


    while (1) {
        vector<string> splitVec, splitVecWithoutComments;
		//! УВАГА -- див. комент до get_current_dir_name() в innerCommands.cpp 
        cout << my_get_current_dir_name() << "$ ";
        getline(cin, userInput);
        if(!userInput.empty()) {
            boost::split(splitVec, userInput, boost::is_any_of(" "), boost::token_compress_on);
            for (string s: splitVec) {
                if (boost::starts_with(s, "#")) {
                    break;
                }
                splitVecWithoutComments.push_back(s);
            }
            if (!splitVecWithoutComments.empty()) {
                if (splitVecWithoutComments[0] == "exit") {
                    break;
                } else {
                    if (std::find(splitVecWithoutComments.begin(), splitVecWithoutComments.end(), "|") != splitVecWithoutComments.end()) 
                    {
                        executeCommand(commandMap["pipeline"], splitVecWithoutComments);
                    }
                    else if (commandMap.find(splitVecWithoutComments[0]) != commandMap.end()) {

                        executeCommand(commandMap[splitVecWithoutComments[0]], splitVecWithoutComments);
                    } else {
                        if (userInput.find("=") != string::npos)
                        {
                            executeCommand(commandMap["assign"], splitVecWithoutComments);
                        } else {
                            cout << splitVecWithoutComments[0] << ": command not found" << endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}



