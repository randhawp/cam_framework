#include "./events.h"
#include "./eventmanager.h"
#include <unistd.h> 
class Camera : public EventManager{
	string name_;
  Event event_;
public:
	explicit Camera(const string& name) : name_(name) {}
  const string& Name() const { return name_; }
  void OnEventReceived(void* pSender, const EventArgs& args) {
		const StringEventArgs* const s = dynamic_cast<const StringEventArgs* const>(&args);
		if (s == nullptr)
			return;
		if (pSender == nullptr)
			return;
	  cout << name_.c_str() << " has -- received " << s->Payload().c_str()  << endl;
    
	}

  
  void takesomepics(){
    long count=0;
    while(1){
      
      string payload="{'msg':'pic capture', 'source':'"+name_+"'}";
      Publish(payload);
      usleep(2000000);

      if(count%10==0){
        string payload="{'msg':'TIMELAPSE capture', 'source':'"+name_+"'}";
        Publish(payload);

      }
      count++;
    }

  }
};