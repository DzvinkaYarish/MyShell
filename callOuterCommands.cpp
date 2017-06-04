//
// Created by dzvinka on 08.04.17.
//

#include <wait.h>
#include "callOuterCommands.h"
#include "innerCommands.h"
//! USE at least "export PATH=$PATH:`pwd`" or getenv()/setenv()
#define EXEC_PATH "/home/dzvinka/CLionProjects/MyShell/cmake-build-debug/"
//! От якби Ви в змінній EXEC_PATH зберігали шлях при запуску -- вважаючи, що
//! всі утиліти разом лежать, було б простіше.
//#define EXEC_PATH ""

int callOuter(std::vector<std::string> args)
{

    if (displayHelp(args))
    {
        return 0;
    }

	//! УВАГА! ТАк само, як підказку, перевірку опцій має робити сама команда!
    if (args.size() < 2 && (args[0] == "mkdir" || args[0] == "rm")) {
        std::cout << args[0] <<": missing operand" << std::endl;
        return -1;
    } else if (args.size() < 3 && (args[0] == "cp" || args[0] == "mv"))
    {
        std::cout << args[0] <<": missing operand" << std::endl;
        return -1;
    }


    std::string expath = EXEC_PATH; 
    expath += args[0];
    char * argv[args.size() + 1];
    for (int i = 0; i < args.size(); i++) {
        argv[i] = (char *)malloc(256); //! <=== Що тут за 256 було?!
        strcpy(argv[i], args[i].c_str());
    }
    strcpy(argv[0], expath.c_str());
    argv[args.size()] = nullptr;
    startNewProcess(argv);
    for (int i = 0; i < args.size() + 1; i++) {
        free(argv[i]);

    }
    return 0 ;
}



int startNewProcess(char * args[])
{
    //int *stats;
    pid_t childPid;
    childPid = fork();
    if (childPid == 0)
    {

        execvp(args[0],  args);
        //execvp("/home/dzvinka/CLionProjects/MyShell/cmake-build/debug/rm", args);
        std::cout << strerror(errno) << std::endl;
		exit(-1); //! УВАГА! Раз вже процес не вдалося запустити, то може дочірній варто зупинити? ;-)
    } else if (childPid < 0)
    {
        std::cout << "balblasjdkfg" << std::endl;
        return -1;
    } else {
        waitpid(-1, nullptr, 0);
    }
    return 0 ;
}
