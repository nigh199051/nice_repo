#include"Sock.h"
#include"event_mgr.h"
#include<unistd.h>
#include<iostream>
#include<vector>
using namespace std;

void handler(int fd,short type0,void* arg)
{
	event_mgr* em=(event_mgr*)arg;
	cout<<"request coming"<<endl;
	vector<Event> ev_vec=em->get_all_events();
	for(vector<Event>::iterator it=ev_vec.begin();it!=ev_vec.end();it++)
	{
		cout<<it->fd<<" "<<fd<<"|"<<it->type0<<" "<<type0<<endl;
		if(it->fd==fd&&it->type0&type0)
		{
			em->del_event(*it);
		}
	}
}

int main()
{
	Sock s;

	s.Bind("127.0.0.1",9999);
	s.Listen();

	//s.Connect("127.0.0.1",9999);
	//s.Write("helloworld",10);
	//char buff[1024]={0};
	//s.Read(buff,1024);
	//cout<<buff<<endl;
	
	event_mgr em;

	Event e;
	e.fd=s.get_fd();
	e.type0=EV_READ|EV_PERSIST;
	e.handler=handler;
	e.arg=(void*)&em;

	
	em.add_event(e);

	while(true)
	{
		em.run();
	}

	return 0;
}
