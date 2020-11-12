//
// Created by lhy on 2020/11/4.
//

#include <string>
#include <iostream>
#include "fpt_pipe.h"
#include "unistd.h"
#include "sys/wait.h"
#include <cstring>

using namespace std;
/*
 * 1. 父进程创建一个管道
 * 2. 创建子进程, 子进程持有管道描述符
 * 3. 父子进程各自关闭管道的一端, 数据在管道之间单向流动.
 */
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
        close(fd[1]);

    }else if(pid > 0){ //父进程读取
        close(fd[1]);   //关闭写描述符
        int readlength = read(fd[0], readStorage, sizeof(readStorage)); //将数据从fd[0]读出
        write(STDOUT_FILENO, readStorage, readlength);
        wait(nullptr);
        close(fd[0]);
    }

}

int ipc_pipe1(void)
{
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    if (pid == 0) {  //child
        close(fd[1]);	                //子进程从管道中读数据，关闭写端
        dup2(fd[0], STDIN_FILENO);		//让wc从管道中读取数据
        execlp("wc", "wc", "-l", NULL);	//wc命令默认从标准读入取数据

    } else {

        close(fd[0]);	//父进程向管道中写数据，关闭读端
        dup2(fd[1], STDOUT_FILENO);		//将ls的结果写入管道中
        execlp("ls", "ls", NULL);		//ls输出结果默认对应屏幕
    }

    return 0;
}

/*
 * 2个子进程写管道, 父进程读管道
 */
int ipc_pipe3(void){

    int fd[2];
    int i = 0;
    pid_t pid;
    char storage[1024];
    int length;

    int ret = pipe(fd);
    if(ret == -1){
        perror("pipe");
        exit(-1);
    }

    for(i = 0; i < 2; i++){
        pid = fork();
        if(pid == -1){
            perror("error");
            exit(-1);
        }else if(pid == 0)
            break;
    }

    if(i == 0){
        close(fd[0]);
        write(fd[1], "hello", strlen("hello"));
        sleep(1);

    }else if (i == 1){
        close(fd[0]);
        write(fd[1], "world", strlen("world"));
        sleep(3);

    }else if(i == 2){
        close(fd[1]);
        while(1){
            length = read(fd[0], storage, 1024);
            if(length > 0){
                cout << length << endl;
                cout << storage << endl;
            } else{
                cout << length << endl;
                break;
            }
        }


        for(int i = 0; i < 2; i++)
            wait(nullptr);
    }


}

