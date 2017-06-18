//
// Created by dzvinka on 08.04.17.
//

#include <wait.h>
#include <sys/stat.h>
#include "callOuterCommands.h"
#include "innerCommands.h"




std::string expath;

int startNewProcessPipes(int pfd[], int pfd2[], int numbInPipeline, std::vector<std::string> args)
{
    std::string localExpath = expath;
    args.push_back("pipe");
    localExpath += "/" + args[0];

    char * argv[args.size() + 1];
    for (int j = 0; j < args.size(); j++) {
        argv[j] = (char *) malloc(256);
        strcpy(argv[j], args[j].c_str());   //doesn;t get name of command
    }
    strcpy(argv[0], localExpath.c_str());
    argv[args.size()] = nullptr;
    if (numbInPipeline == 0)
    {

        switch (fork()) {
            case -1:
                exit(-1);

            case 0:                                         //  exec  to write to pipe */
                if (close(pfd[0]) == -1)                    // Read end is unused //
                    exit(-1);



                if (pfd[1] != STDOUT_FILENO) {
                    if (dup2(pfd[1], STDOUT_FILENO) == -1)
                        exit(-1);
                    if (close(pfd[1]) == -1)
                        exit(-1);
                }
                execvp(argv[0], argv);
                std::cout <<"Invalid command: " << args[0] << std::endl;
                //std::cout << strerror(errno) << std::endl;/* Writes to pipe */
                exit(0);

            default:            /* Parent falls through to create next child */
                break;
        }

    } else if (numbInPipeline < 0) //last process in pipeline
    {
        switch (fork()) {
            case -1:
                exit(-1);

            case 0:                                         //exec to read from pipe */

                if (close(pfd[1]) == -1)                    // Write end is unused //
                    exit(-1);



                if (pfd[0] != STDIN_FILENO) {
                    if (dup2(pfd[0], STDIN_FILENO) == -1)
                        exit(-1);
                    if (close(pfd[0]) == -1)
                        exit(-1);
                }
                execvp(argv[0], argv);
                //std::cout << strerror(errno) << std::endl;
                std::cout <<"Invalid command: " << args[0] << std::endl;
                exit(0);

            default: /* Parent falls through */
                break;
        }
    } else {  //process in the middle
        switch (fork()) {
            case -1:
                exit(-1);

            case 0:


                if (close(pfd[1]) == -1)                    // Write end is unused for first pipe
                    exit(-1);

                if (pfd[0] != STDIN_FILENO) {
                    if (dup2(pfd[0], STDIN_FILENO) == -1)
                        exit(-1);
                    if (close(pfd[0]) == -1)
                        exit(-1);
                }

                if (close(pfd2[0]) == -1)                    // Read end is unused for second pipe
                    exit(-1);


                if (pfd2[1] != STDOUT_FILENO) {
                    if (dup2(pfd2[1], STDOUT_FILENO) == -1)
                        exit(-1);
                    if (close(pfd2[1]) == -1)
                        exit(-1);
                }

                execvp(argv[0], argv);
                //std::cout << strerror(errno) << std::endl;
                std::cout <<"Invalid command: " << args[0] << std::endl;
                exit(0);

            default: /* Parent falls through */
                break;
        }
    }
    return 0;
}


int organizePipes(std::vector<std::string> args)
{

    expath = args[args.size() - 1];
    args.erase(args.begin() + (args.size() - 1));
    int i = 0, numbOfProcess = 1, k = 0;
    for(int j = 0; j < args.size(); j++)
    {

        if (strcmp(args[j].c_str(), "|") == 0)
        {
            numbOfProcess++;
        }
    }
    //std::cout << numbOfProcess << std:: endl;
    int pipes[numbOfProcess][2];
    while (k != numbOfProcess) {
        std::vector<std::string> forOneCmd;
        while (strcmp(args[i].c_str(), "|") != 0) {
            forOneCmd.push_back(args[i]);
            i++;
            if (i == args.size())
            {
                break;
            }
        }
        i++;
        if (k == 0) {   //first process

            pipe(pipes[k]);
            startNewProcessPipes(pipes[k], pipes[k + 1], k, forOneCmd);
        } else if (k == numbOfProcess - 1)
        {

            startNewProcessPipes(pipes[k - 1], pipes[k], -k, forOneCmd); //last process
        } else
        {

            pipe(pipes[k]);
            startNewProcessPipes(pipes[k - 1], pipes[k], k, forOneCmd);  //process in the middle
        }
        k++;
    }

    // Parent closes unused file descriptors for pipe, and waits for children

    for(int n = 0; n < numbOfProcess - 1; n++) {

        if (close(pipes[n][0]) == -1)
            exit(-1);
        if (close(pipes[n][1]) == -1)
            exit(-1);
    }
    for(int n = 0; n < numbOfProcess ; n++) {
        if (wait(NULL) == -1)
            exit(-1);
    }

    return 0;
}


int callOuter(std::vector<std::string> args)
{

    expath = args[args.size() - 1];
    args.erase(args.begin() + (args.size() - 1));
    bool inbackground = false;
    for (int i  = 0; i < args.size(); i++)
    {
        if (strcmp(args[i].c_str(), "&") == 0)
        {
            inbackground = true;
            args.erase(args.begin() + i, args.end());
        }
    }

    expath += "/" + args[0];

    char * argv[args.size() + 1];
    for (int i = 0; i < args.size(); i++) {
        argv[i] = (char *)malloc(256);
        strcpy(argv[i], args[i].c_str());   //doesn;t get name of command
    }
    strcpy(argv[0], expath.c_str());
    argv[args.size()] = nullptr;
    startNewProcess(argv, inbackground);
    for (int i = 0; i < args.size() + 1; i++) {
        free(argv[i]);

    }
    return 0 ;
}



int startNewProcess(char * args[], bool inbackground)
{
    //int *stats;
    pid_t childPid;
    childPid = fork();
    if (childPid == 0)
    {
        if (inbackground)  //run a daemon process
        {
            pid_t  pid2;
            pid2 = fork();
            if (pid2 < 0)
            {
                return -1;

            } else if (pid2 > 0) {
                exit(EXIT_SUCCESS);
            }
            if (setsid() < 0) {
                exit(EXIT_FAILURE);
            }
            umask(0);
            for (int x = sysconf(_SC_OPEN_MAX); x>=0; x--)
            {
                close (x);
            }
            execvp(args[0],  args);
            std::cout << strerror(errno) << std::endl;
            exit(-1);

        } else {
            execvp(args[0], args);
            //execvp("/home/dzvinka/CLionProjects/MyShell/cmake-build/debug/rm", args);
            std::cout << strerror(errno) << std::endl;
            exit(-1);
        }
    } else if (childPid < 0)
    {
        //std::cout << "balblasjdkfg" << std::endl;
        return -1;
    } else {
        waitpid(-1, nullptr, 0);
    }
    return 0 ;
}


