//
// Created by 78472 on 2020/10/15.
//

#ifndef FILE_PROCESS_THREAD_ENVIRON_H
#define FILE_PROCESS_THREAD_ENVIRON_H

/*
 * 三个函数定义于<stdlib.h>中
 * char *getenv(const char *name);
 * 成功： 返回环境变量的值； 失败： NULL (name 不存在)
 *
 * int setenv(const char *name, const char *value, int overwrite);
 * 成功： 0； 失败： -1
 * 参数 overwrite 取值：
 *      0： 不覆盖。 (该参数常用于设置新环境变量， 如： ABC = haha-day-night)
 *      1： 覆盖原环境变量
 *
 * int unsetenv(const char *name);
 * 成功： 0； 失败： -1
 * 注意事项： name 不存在仍返回 0(成功)， 当 name 命名为"ABC="时则会出错。
 *
 */


int printEnviron();

char * my_getenv(const char *name);

void envOperate(void);












#endif //FILE_PROCESS_THREAD_ENVIRON_H
