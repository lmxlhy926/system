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
    int status;
    pid_t waitpid;
    pid_t pid = fork();

    if(pid == -1){
        perror("fork failed");
        exit(-1);
    }else if(pid == 0){
        cout << "i am child, my pid == " << getpid() << endl;
        sleep(3);
        cout << "child dile -----" << endl;
        exit(100);
    }else if(pid > 0){
        cout << "i am parent, my pid == " << getpid() << " my son pid == " << pid << endl;
        waitpid = wait(&status);

        if(waitpid == -1){
            perror("wait failed");
            exit(-1);
        }

        if(WIFEXITED(status)){
            cout << "child exit with status " << WEXITSTATUS(status) << endl;
        }else if (WIFSIGNALED(status)){
            cout << "child is killed by " << WTERMSIG(status) << endl;
        }else if(WIFSTOPPED(status)){
            cout << "child is stopped by " << WSTOPSIG(status) << endl;
        }
    }

}