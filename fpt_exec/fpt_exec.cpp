//
// Created by 78472 on 2020/10/23.
//

#include <cstdio>
#include "unistd.h"
#include <iostream>

using namespace std;


char * const argv[] = {const_cast<char *>("ls"), const_cast<char *>("-l"), nullptr};

extern char **environ;

int fptExec(int option)
{
    pid_t pid = fork();
    if(pid == 0){
        switch(option){
            case 0:
                execl("/bin/ls", "ls", "-l", nullptr);
                perror("error: ");
                break;
            case 1:
                execlp("ls", "ls", "-l", nullptr);
                perror("error: ");
                break;
            case 2:
                execle("/bin/ls", "ls", "-l", nullptr, environ);
                perror("error: ");
                break;
            case 3:
                execv("/bin/ls", argv);
                perror("error: ");
                break;
            case 4:
                execvp("ls", argv);
                perror("error: ");
                break;
            case 5:
                execve("/bin/ls", argv, environ);
                perror("error: ");
                break;
            default:
                cout << "wrong option number" << endl;
        }
    }else if(pid > 0){
        cout << "i am parent, pid = " << getpid() << endl;
    }

}


























