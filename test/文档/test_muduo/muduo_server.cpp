/*
muduo库 TcpServer  Tcpclient

epoll + 线程池
把网络I/O和业务代码分开
            用户的连结与断开  用户的可读写事件
*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
#include <string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
// 基于muduo开发服务器程序
/*
1、组合TcpServer对象
2、创建EventLoop事件循环对象的指针
3、明确TcpServer构造函数的参数，输出ChatServer的构造函数
4、在当前服务器类的构造函数当中，注册处理链接的回调函数和处理读写事件的回调函数
5、设置合适的服务端线程数量，muduo库会自己分配io线程和work线程
*/
class ChatServer
{
public:
    ChatServer(EventLoop *loop,               // 事件循环
               const InetAddress &listenAddr, // IP + Port
               const string &nameArg)         // 服务器的名字
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 给服务器注册用户连接的创建和断开回调
        _server.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));
        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(bind(&ChatServer::onMessage, this, _1, _2, _3));
        // 设置服务器端的线程数量， 1个io线程  3个work线程
        _server.setThreadNum(4);
    }

    void start()
    {
        _server.start();
    }

private:
    // 专门处理用户的链接创建和断开 listenfd accept
    void onConnection(const TcpConnectionPtr &conn)
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state:online" << endl;
        }
        else
       {            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << "state:offline" << endl;
            conn->shutdown();

        }
    }
    // 专门处理用户读写事件
    void onMessage(const TcpConnectionPtr &conn,
                   Buffer *buffer,
                   Timestamp time)  // 接收到数据的事件信息
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data:" << buf << "time:" << time.toString() << endl;
        conn->send(buf);
    }
    TcpServer _server;
    EventLoop *_loop;
};

int main(){
    EventLoop loop;
    InetAddress addr("192.168.230.128", 6000);
    ChatServer server(&loop, addr, "ChatServer");
    server.start(); // listenfd epoll_ctl =》 epoll
    loop.loop(); // epoll_wait 以阻塞方式等待新用户链接，已连接用户的读写事件等
    return 0;
}