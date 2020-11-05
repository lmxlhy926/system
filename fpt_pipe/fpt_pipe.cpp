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
    int fd[2];  //fd[0]存储读描述符, fd[1]存储写描述符。
    string str = "ipc test";
    char readStorage[10];

    int ret = pipe(fd);
    if(ret == -1){
        perror("pipe");
        exit(-1);
    }
    pid = fork();
    if(pid == -1){
        perror("fork");
        exit(-1);
    }else if(pid == 0){ //子进程写
        close(fd[0]);   //关闭读描述符
        sleep(1);
        write(fd[1], str.c_str(), str.length()); //将数据写入fd[1]

    }else if(pid > 0){ //父进程读取
        close(fd[1]);   //关闭写描述符
        int readlength = read(fd[0], readStorage, sizeof(readStorage)); //将数据从fd[0]读出
        write(STDOUT_FILENO, readStorage, readlength);
        wait(nullptr);
    }

}