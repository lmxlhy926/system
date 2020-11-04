//
// Created by 78472 on 2020/10/24.
//

#ifndef FILE_PROCESS_THREAD_FPT_WAITPID_H
#define FILE_PROCESS_THREAD_FPT_WAITPID_H

/*
 * pid_t wait(int *status);
 * 成功：返回清理掉的子进程 ID； 失败：-1 (没有子进程)
 *
 * pid_t waitpid(pid_t pid, int *status, in options);
 * 成功： 返回清理掉的子进程 ID；    失败： -1(无子进程)；   0：options为WNOHANG, 子进程正在运行中
 * 参数：
 *      pid：
 *          > 0：回收指定 ID 的子进程
 *           -1：回收任意子进程（相当于 wait）
 *      status:
 *          接收进程返回状态
 *      options:
 *          0: 阻塞等待
 *          WNOHANG: 不阻塞
 *
 * 判断进程返回状态的宏函数
 *      WIFEXITED(status) 为非 0 → 进程正常结束
 *      WEXITSTATUS(status) 如上宏为真， 使用此宏 → 获取进程退出状态 (exit 的参数)
 *
 *      WIFSIGNALED(status) 为非 0 → 进程异常终止
 *      WTERMSIG(status) 如上宏为真， 使用此宏 → 取得使进程终止的那个信号的编号。
 *
 *      WIFSTOPPED(status) 为非 0 → 进程处于暂停状态
 *      WSTOPSIG(status) 如上宏为真， 使用此宏 → 取得使进程暂停的那个信号的编号。
 */

int fpt_wait();




#endif //FILE_PROCESS_THREAD_FPT_WAITPID_H
