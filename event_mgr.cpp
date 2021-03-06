#include"event_mgr.h"
#include<iostream>
#include<signal.h>
#include<vector>




event_mgr::event_mgr()
{
	this->base=event_init();
}

void event_mgr::add_event(Event& e)
{
	//struct event ev;
	event *tmp=event_new(this->base,e.fd,e.type0,e.handler,e.arg);
	e.ev=tmp;
	//event_set(tmp,fd,type0,handler,tmp);	
	
	//pack mux and event
	/*
	int** pack=(int**)(new void*[2]);
	pack[0]=(int*)arg;
	pack[1]=(int*)tmp;
	event_set(tmp,fd,type0,handler,pack);	
	*/
	event_set(e.ev,e.fd,e.type0,e.handler,e.arg);
	//
	
	//event_set(tmp,fd,type0,handler,arg);	
	event_add(e.ev,NULL);
	//event_set(&ev,fd,type0,foo,&ev);
	//event_add(&ev,NULL);
	ev_vec.push_back(e);
}

void event_mgr::del_event(Event e)
{
	//event e;
	//event_active(&e,EV_READ|EV_PERSIST,1);
	for(std::vector<Event>::iterator it=ev_vec.begin();it!=ev_vec.end();)
	{
		if(e.fd==it->fd&&(e.type0&it->type0))
		{
			event_del(it->ev);
			ev_vec.erase(it);
			//e.ev=NULL;
		}
		else
		{
			it++;
		}
	}
		
}

void event_mgr::run()
{
	//event_base_dispatch(this->base);
	event_dispatch();
}

void event_mgr::add_sig_event(Event& e)
{
	event *sigobj=event_new(base,e.fd,e.type0,e.handler,e.arg);
	event_set(sigobj,e.fd,e.type0,e.handler,e.arg);
	event_add(sigobj,NULL);
	ev_vec.push_back(e);
}

std::vector<Event> event_mgr::get_all_events()
{	
	return ev_vec;	
}
