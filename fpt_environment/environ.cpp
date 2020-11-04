//
// Created by 78472 on 2020/10/15.
//

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

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
    printf("******value = %s\n", value);

    setenv("ABC", "abcvalue", 0);
    printf("******value = %s\n", getenv("ABC"));
    printEnviron();

    int ret = unsetenv("ABC");
    cout << "******ret = " << ret << endl;
    printEnviron();
}


