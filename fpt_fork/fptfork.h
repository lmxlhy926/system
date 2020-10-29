//
// Created by 78472 on 2020/10/17.
//

#ifndef FILE_PROCESS_THREAD_FPTFORK_H
#define FILE_PROCESS_THREAD_FPTFORK_H

/*
 * 父子进程之间遵循读时共享写时复制的原则，目的是节省内存开销，逻辑上各个进程的变量之间是独立的。
 *
 * 父子进程之间共享：1.文件描述符 2.mmap建立的映射区
 */

extern int var;

int fork_loop(int num);






#endif //FILE_PROCESS_THREAD_FPTFORK_H
