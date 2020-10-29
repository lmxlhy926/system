//
// Created by 78472 on 2020/10/23.
//

#ifndef FILE_PROCESS_THREAD_FPT_EXEC_H
#define FILE_PROCESS_THREAD_FPT_EXEC_H

/*
 * 可执行程序名（相对位置/绝对位置），PATH环境变量，整个环境变量environ
 * 参数形式：list vector
 * 环境变量：PATH environ
 *
 * int execl(const char *path, const char *arg, ...);
 * int execlp(const char *file, const char *arg, ...);
 * int execle(const char *path, const char *arg, ..., char *const envp[]);
 *
 * vector path environ
 * int execv(const char *path, char *const argv[]);
 * int execvp(const char *file, char *const argv[]);
 * int execve(const char *path, char *const argv[], char *const envp[]);
 *
 */

int fptExec(int option);


#endif //FILE_PROCESS_THREAD_FPT_EXEC_H
