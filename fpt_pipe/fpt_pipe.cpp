//
// Created by lhy on 2020/11/4.
//

#include <string>
#include <iostream>
#include "fpt_pipe.h"
#include "unistd.h"
#include "sys/wait.h"


using namespace std;
int ipc_pipe(void){
    pid_t pid;
    int fd[2];
    string str = "ipc test";
    char readStorage[10];

    pipe(fd);
    pid = fork();
    if(pid == -1){
        perror("fork");
        exit(-1);
    }else if(pid == 0){ //子进程写
        close(fd[0]);
        sleep(1);
        write(fd[1], str.c_str(), str.length());

    }else if(pid > 0){ //父进程读取
        close(fd[1]);
        read(fd[0], readStorage, str.length());
        cout << readStorage << endl;
        wait(nullptr);

    }

}