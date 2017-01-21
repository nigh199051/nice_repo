#include "Sock.h"

Sock::Sock()
{
	sock=socket(AF_INET,SOCK_STREAM,0);
}

Sock::Sock(int s)
{
	sock=s;
}

int Sock::get_fd()
{
	return sock;
}

void Sock::set_nonblock()
{
	int flags=fcntl(sock,F_GETFL,0);
	flags|=O_NONBLOCK;
	fcntl(sock,F_SETFL,flags);
}

void Sock::set_reuse()
{
	int reuse=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int));
}

int Sock::Listen()
{
	return listen(sock,1024);
}

int Sock::Bind(std::string ip,int port)
{
	sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=inet_addr(ip.c_str());
	local.sin_port=htons(port);

	return bind(sock,(sockaddr*)&local,sizeof(local));
}

Sock Sock::Accept(sockaddr* remote,socklen_t *len)
{

	int handlefd=accept(sock,remote,len);	

	Sock handle_sock(handlefd);

	return handle_sock;
}

int Sock::Connect(std::string ip,int port)
{
	sockaddr_in remote;
	remote.sin_family=AF_INET;
	remote.sin_addr.s_addr=inet_addr(ip.c_str());
	remote.sin_port=htons(port);
	return connect(sock,(sockaddr*)&remote,sizeof(remote));
}


int Sock::Read(char *buff,int len)
{
	return read(sock,buff,len);
}

int Sock::Write(char *buff,int len)
{
	return write(sock,buff,len);
}







