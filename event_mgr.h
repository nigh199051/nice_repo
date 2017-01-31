#ifndef EVENT_MGR_H
#define EVENT_MGR_H

#include<event.h>

class event_mgr
{
public:
	event_mgr();
	void add_event(int fd,short type0,void (*handler)(int,short,void*),void* arg);
	void del_event(event*);
	void add_sig_event(int sig,void (*sig_handler)(int,short,void*),void* arg);
	void run();
private:
	struct event_base *base;	
};

#endif
