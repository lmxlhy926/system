//
// Created by 78472 on 2020/10/24.
//

#include "fptfork.h"
#include <cstdio>
#include <cstdlib>
#include "unistd.h"
#include "sys/wait.h"
#include <iostream>

using namespace std;

int fpt_wait(){
    int index = 0;
    int status = 0;
    int completeFlag = 0;
    pid_t pid = -1, waitPid = -1;
    int loopnum = 5;

    for(index = 0; index < loopnum; index++){
        pid = fork();
        if(pid == 0)
            break;
    }

    if(pid == -1){
        perror("fork failed");
        exit(-1);

    }else if(pid == 0){
        cout << "i am " << index << " child, my pid == " << getpid() << " my parentpid == " << getppid() << endl;
        sleep(3);
        exit(index);

    }else if(pid > 0){
        cout << "i am parent, my pid == " << getpid() << endl;

        do{
            waitPid = waitpid(-1, &status, WNOHANG);
            if(waitPid > 0){
                if(WIFEXITED(status)){
                    cout << "child exit with status " << WEXITSTATUS(status) << endl;
                }else if (WIFSIGNALED(status)){
                    cout << "child is killed by " << WTERMSIG(status) << endl;
                }else if(WIFSTOPPED(status)){
                    cout << "child is stopped by " << WSTOPSIG(status) << endl;
                }
                completeFlag++;
            }
        }while(completeFlag < loopnum);

    }

}


