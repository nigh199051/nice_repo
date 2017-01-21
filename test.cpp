#include"Sock.h"
#include<unistd.h>
#include<iostream>
using namespace std;

int main()
{
	Sock s;

	//s.Bind("127.0.0.1",9999);
	//s.Listen();
	//s.Accept(NULL,NULL);

	s.Connect("127.0.0.1",9999);
	s.Write("helloworld",10);
	char buff[1024]={0};
	s.Read(buff,1024);
	cout<<buff<<endl;

	return 0;
}
