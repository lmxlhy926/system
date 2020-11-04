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
 *
 */

int ipc_pipe(void);


#endif //FILE_PROCESS_THREAD_FPT_PIPE_H
