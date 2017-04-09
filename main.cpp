#include <boost/lambda/lambda.hpp>
#include "callOuterCommands.h"
#include "innerCommands.h"
#include <fstream>

//#include <map>

//using namespace boost::filesystem;

using namespace std;   /// BBBBBBBBBBBAAADDDDD

typedef int (* commandToExec)(vector<string> args);
map<string, commandToExec> commandMap;



int executeCommand(commandToExec commnd, vector<string> args)
{
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
        vector<string> splitVec;
        boost::split(splitVec, line, boost::is_any_of(" "), boost::token_compress_on);
        if (splitVec[0] == "exit") {
            break;
        }
        else if (commandMap.find(splitVec[0]) != commandMap.end()) {
            executeCommand(commandMap[splitVec[0]], splitVec);
        } else {
            cout << splitVec[0] << ": command not found" << endl;
        }
    }
    return 0;
}



int main()
{
    commandMap["ls"] = &callOuter;
    commandMap["cd"] = &cd;
    commandMap["pwd"] = &pwd;

    //commandMap["exit"] = &exit;
    commandMap["mkdir"] = &callOuter;
    commandMap["rm"] = &callOuter;
    commandMap["mv"] = &callOuter;
    commandMap["cp"] = &callOuter;
    commandMap["myshell"] = &readScript;
    string userInput;
    vector<string> splitVec;
    while (1) {
        cout << get_current_dir_name() << "$ ";
        getline(cin, userInput);

        boost::split(splitVec, userInput, boost::is_any_of(" "), boost::token_compress_on);
        if (splitVec[0] == "exit") {
            break;
        } else {
            if (commandMap.find(splitVec[0]) != commandMap.end()) {

                executeCommand(commandMap[splitVec[0]], splitVec);
            } else {
                cout << splitVec[0] << ": command not found" << endl;
            }
        }
    }
    return 0;
}



