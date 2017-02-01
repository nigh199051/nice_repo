#ifndef EVENT_MGR_H
#define EVENT_MGR_H

#include<event.h>
#include<vector>

struct Event
{
	int fd;
	short type0;
	void (*handler)(int,short,void*);
	void* arg;
	event* ev;
};

class event_mgr
{
public:
	event_mgr();
	void add_event(Event&);
	void del_event(Event);
	void add_sig_event(Event&);
	void run();
	std::vector<Event> get_all_events();
private:
	struct event_base *base;	
	std::vector<Event> ev_vec;
};

#endif
