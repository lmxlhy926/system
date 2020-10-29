//
// Created by 78472 on 2020/10/15.
//

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;
/*
 * 本质：char *envron[] = {"HOME=/home/itcat", "SHELL=/bin/bash", ....}
 * 所有的环境变量都存在于environ这个数组中
 */
extern char **environ;

/* 打印当前环境下的所有环境变量 */
int printEnviron()
{
    for(int i = 0; environ[i] != nullptr; i++){
        printf("%s\n", environ[i]);
    }
    return 0;
}

char * my_getenv(const char *name)
{
    char *p = nullptr;

    for(int i = 0; environ[i] != nullptr; i++){
        p = strstr(environ[i], "=");
        int len = p - environ[i];
        if(strncmp(name, environ[i], len) == 0){
            return p+1;
        }
    }
    return nullptr;
}

void envOperate(){

    char *value = getenv("ABC");
    printf("value = %s\n", value);

    setenv("ABC", "abcvalue", 0);
    value = getenv("abc");
    cout << R"(getenv("abc") = )" << value << endl;

    int ret = unsetenv("abc");
    cout << "ret = " << ret << endl;

    printEnviron();
}


