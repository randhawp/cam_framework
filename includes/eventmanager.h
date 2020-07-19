#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "./events.h"
#include <unistd.h> 
class EventManager{
	string name_;
  Event event_;
public:

  virtual void OnEventReceived(void* pSender, const EventArgs& args)=0;
  void Publish(const string& message)  {
		event_(this, StringEventArgs(message));
	}
	long Register(function<void(void*, const EventArgs&)> f)  {
		return event_.Subscribe(f);
	}
	void Unregister(long token)  {
		event_.Unsubscribe(token);
	}
  
};
#endif