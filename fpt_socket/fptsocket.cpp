//
// Created by lhy on 2020/12/19.
//
#include "fptsocket.h"

#include "netinet/in.h"     //IP地址+port结构体
#include "sys/socket.h"     //socket
#include "arpa/inet.h"      //inet_pton
#include "unistd.h"         //read, write

#include <cstring>
#include <cstdio>
#include <cctype>
#include <string>
#include <iostream>
#include <chrono>

#include <future>
#include <thread>

using namespace std;
#define MAXLINE 80
#define SERV_PORT 60000

namespace sock{

    int sockClient(){

        struct sockaddr_in serveraddr {};   //ipv4服务器地址结构体(ip+port)
        char buf[MAXLINE];
        int sockfd, n;
        string str = "hello world";

    //生成客户端通信用的socket, 建立连接时自动分配ip和port
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //给服务器结构体配置地址
        bzero(&serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;    //ipv4协议
        inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr.s_addr);  //ip地址
        serveraddr.sin_port = htons(SERV_PORT); //端口号

    //和服务器建立连接
        connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    //接收/发送消息
        write(sockfd, str.c_str(), str.size());
        n = read(sockfd, buf, MAXLINE);
        (cout << "client: response from server: ").flush();
        write(STDOUT_FILENO, buf, n);
        cout << endl;

    //关闭连接
        this_thread::sleep_for(chrono::milliseconds(1000));
        close(sockfd);

        return 0;
    }


    int sockserver(){
        struct sockaddr_in serveraddr{}, clientaddr{};
        socklen_t clientaddr_len;
        int listenfd, connfd;
        char buf[MAXLINE] {};
        char str[INET_ADDRSTRLEN] {};
        int i, n;

        //创建监听socket
        listenfd = socket(AF_INET, SOCK_STREAM, 0);

        //设置(ip + port)
        bzero(&serveraddr, sizeof(serveraddr));
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        serveraddr.sin_port = htons(SERV_PORT);

        //给listenfd绑定监听地址
        bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

        //监听指定的(ip + port)
        listen(listenfd, 20);

        printf("server: Accept connections ....\n");
        while(1){

            clientaddr_len = sizeof(clientaddr);

            //和其中一个客户端请求建立连接, 创建出用于通信的connect socket, 并返回建立连接的客户端的(ip + port)
            connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddr_len);

            n = read(connfd, buf, MAXLINE);
            cout << "n: " << n << endl;

            printf("server: received from %s at port %d\n",
                    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, str, sizeof(str)),
                    ntohs(clientaddr.sin_port));

            if(n == 0){
                cout << "server: client closed" << endl;
                close(connfd);
                return 0;
            }

            for(i = 0; i < n; i++){
                buf[i] = toupper(buf[i]);
            }

            write(connfd, buf, n);
        }


    }


    void run(){
        auto server = std::async(std::launch::async, sockserver);

        this_thread::sleep_for(chrono::milliseconds(1000));

        auto client = std::async(std::launch::async, sockClient);
    }




}

