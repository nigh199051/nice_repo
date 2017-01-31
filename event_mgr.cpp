#include"event_mgr.h"
#include<iostream>
#include<signal.h>
#include<vector>




event_mgr::event_mgr()
{
	this->base=event_init();
}

void event_mgr::add_event(int fd,short type0,void (*handler)(int,short,void*),void* arg)
{
	//struct event ev;
	event *tmp=event_new(this->base,fd,type0,handler,arg);
	//event_set(tmp,fd,type0,handler,tmp);	
	
	//pack mux and event
	int** pack=(int**)(new void*[2]);
	pack[0]=(int*)arg;
	pack[1]=(int*)tmp;
	event_set(tmp,fd,type0,handler,pack);	
	//
	
	//event_set(tmp,fd,type0,handler,arg);	
	event_add(tmp,NULL);
	//event_set(&ev,fd,type0,foo,&ev);
	//event_add(&ev,NULL);
}

void event_mgr::del_event(event* e)
{
	//event e;
	//event_active(&e,EV_READ|EV_PERSIST,1);
	event_del(e);
}

void event_mgr::run()
{
	//event_base_dispatch(this->base);
	event_dispatch();
}

void event_mgr::add_sig_event(int sig,void (*sig_handler)(int,short,void*),void* arg)
{
	event *sigobj=event_new(base,sig,EV_SIGNAL|EV_PERSIST,sig_handler,arg);
	event_set(sigobj,sig,EV_SIGNAL|EV_PERSIST,sig_handler,arg);
	event_add(sigobj,NULL);
}
