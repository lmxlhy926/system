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


/*
 * 将STDIN_FILENO指向管道的读端
 * 将STDOUT_FILENO指向管道的写端
 * 这样本来对标准输入输出文件进行操作的函数, 就可以对管道进行操作.
 */
int ipc_pipe1(void)
{
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    if (pid == 0) {  //child
        close(fd[1]);
//        dup2(fd[0], STDIN_FILENO);		//STDIN_FILENO指向管道的读端
//        execlp("wc", "wc", "-l", NULL);	//wc命令默认从STDIN_FILENO指向的文件读取数据, 现在就是从管道读取数据.
        char buf[1000];
        int length = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, length);

    } else {

        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);		//STDOUT_FILENO指向管道的写端
        execlp("ls", "ls", NULL);	//ls的结果默认是输出到STDOUT_FILENO指向的文件, 现在STDOUT_FILENO指向管道,因此数据被写入到管道中

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

    if(i == 0){ //子进程1
        close(fd[0]);
        write(fd[1], "hello", strlen("hello"));

    }else if (i == 1){  //子进程2
        close(fd[0]);
        write(fd[1], "world", strlen("world"));
        sleep(3);

    }else if(i == 2){
        close(fd[1]);
        while(1){   //当子进程结束后管道的写端都会关闭, 此时父进程再读管道, read返回0.
           length = read(fd[0], storage, 1024);
            if(length > 0){
                cout << length << " : "<<  storage << endl;
            } else{
                cout << length << endl;
                break;
            }
        }


        for(int i = 0; i < 2; i++)
            wait(nullptr);
    }


}

