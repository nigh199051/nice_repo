#ifndef SOCK_H
#define SOCK_H

#include<sys/socket.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<string>

class Sock
{
public:
	Sock();
	Sock(int fd);
	int get_fd();
	void set_nonblock();
	void set_reuse();
	int Listen();
	int Bind(std::string ip,int port);
	int Connect(std::string ip,int port);
	Sock Accept(sockaddr* remote,socklen_t* len);
	int Write(char *buff,int len);
	int Read(char *buff,int len);
private:
	int sock;
};

#endif
