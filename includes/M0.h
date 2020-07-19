#include "./events.h"
#include <unistd.h> 
class M0 : public EventManager{
	string name_;
  Event event_;
public:
	explicit M0(const string& name) : name_(name) {}
  const string& Name() const { return name_; }
	void OnEventReceived(void* pSender, const EventArgs& args) {
		const StringEventArgs* const s = dynamic_cast<const StringEventArgs* const>(&args);
		if (s == nullptr)
			return;
		if (pSender == nullptr)
			return;
		
		cout << name_.c_str() << " has -- received " << s->Payload().c_str() << endl;
    
	}

  
  void Check_mo_msg(){
    while(1){
      string payload="{'msg':'M0 message', 'source':'"+name_+"'}";
      Publish(payload);
      usleep(3000000);
    }

  }
};