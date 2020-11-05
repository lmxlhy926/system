//
// Created by lhy on 2020/11/4.
//

#ifndef FILE_PROCESS_THREAD_FPT_PIPE_H
#define FILE_PROCESS_THREAD_FPT_PIPE_H

/*
 * linux环境下，进程地址空间相互独立，每个进程各自有不同的用户地址空间。
 * 任何一个进程的全局变量在另一个进程中都看不到，所以进程和进程之间不能相互访问。
 * 交换数据必须通过内核，在内核中开辟一块缓冲区，进程1把数据从用户空间拷贝到内核缓冲区，
 * 进程2再从内核缓冲区把数据读走，内核提供的这种机制称为进程间通信。
 *
 * 常用的进程间通信方式
 *      管道（使用最简单）
 *      信号（开销最小）
 *      共享映射区（无血缘关系）
 *      本地套接字（最稳定)
 */

/*
 * 管道
 * 管道是一种最基本的IPC机制，作用于有血缘关系的进程之间，完成数据传递。
 *  1.本质是一个伪文件（实际为内核缓冲区）
 *  2.由2个文件描述符引用，一个表示读端，一个表示写端。
 *  3.规定数据从管道的写端流入管道，从读端流出。
 *
 * 局限性
 *  数据自己读不能自己写
 *  数据一旦被读走，便不再在管道中存在，不可反复读取
 *  采用的是半双工通信方式，一条管道的数据只能有一个流动方向
 *  只能在有公共祖先的进程间使用管道
 */


/*
 * int pipe(int pipefd[2]); 成功:0； 失败:-1； 设置errno.
 *  函数调用成功后返回r/w两个文件描述符。无需open，但是需要手动close。fd[0] --> read; fd[1] --> write.
 *
 * 使用方式：
 *  1. 父进程调用pipe函数创建管道，得到2个文件描述符fd[0],fd[1],指向管道的读端和写端。
 *  2. 父进程调用fork()创建子进程，那么子进程也有2个文件描述符指向同一管道。
 *  3. 一端关闭读端，一端关闭写端。数据从写端流入，读端流出，实现了通信。
 *
 * 管道的读写行为：
 *      读管道：
 *          1.管道中有数据, read返回实际读到的字节数。
 *          2.管道中无数据：
 *              .管道写端被全部关闭, read返回0(好像读到文件结尾)
 *              .写端没有全部关闭, read阻塞等待
*        写管道：
 *          1.管道读端全部被关闭, 进程异常终止(也可捕捉SIGPIPE信号，使进程不终止)
 *          2.管道读端没有全部关闭：
 *              管道已满, write阻塞。
 *              管道未满, write将数据写入，并返回实际写入的字节数
 *
 * 管道的缺点：
 *      1. 只能单向通信, 双向通信需建立两个管道。
 *      2. 只能用于父子、兄弟进程间的通信。该问题后来使用fifo有名管道解决。
 */


int ipc_pipe(void);


#endif //FILE_PROCESS_THREAD_FPT_PIPE_H
