//
// Created by 78472 on 2020/10/17.
//

#include "fptfork.h"
#include <unistd.h>
#include <iostream>

using namespace std;

/*
 * fork之后
 * 父子相同处：.data .text 堆 栈 环境变量 用户id 宿主目录 进程工作目录 信号处理方式
 * 父子不同处：1.进程id  2.fork返回值  3.父进程Id  4.进程运行时间  5.闹钟（定时器）  6.未决信号集
 * 注：相同的意思是值相同,不代表物理存储空间相同
 */

int var = 20;

/*
 * 循环创建n个子进程, 所有的子进程的父进程是相同的
 */
int fork_loop(int num){
    int i;

    if(num < 0)
    {
        cout << "num cant less than 0" << endl;
        exit(-1);
    }

    for(i = 0; i < num; i++) //循环创建num个子进程
    {
        pid_t pid = fork(); //fork之后产生一个子进程，子进程程序执行位置和当前进程执行位置一致，并开始并行运行。
        //新产生的进程的执行位置开始处。
        if(pid == -1)
            exit(-1);
        else if (pid == 0)  //所有的子进程不再执行fork.
            break;
    }

    if(i == num){   //父进程执行分支
        sleep(num);
        cout << "i am parent, my id = " << getpid() << " var = " << var << endl;

    }else{  //各个子进程执行分支
        var = i;
        sleep(i);
        cout << "i am " << i + 1 << "th son, " << "my id = " << getpid()
             << ", my parent id = " << getppid() << " var = " << var << endl;
    }

    return 0;
}





















