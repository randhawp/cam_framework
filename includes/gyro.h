#include "./events.h"
using namespace std;
class Gyro : public EventManager {
	Event event_;
	string name_;

public:
	explicit Gyro(const string& name) : name_(name) {}
  const string& Name() const { return name_; }
  void OnEventReceived(void* pSender, const EventArgs& args) {
		const StringEventArgs* const s = dynamic_cast<const StringEventArgs* const>(&args);
		if (s == nullptr)
			return;
		if (pSender == nullptr)
			return;
	
		cout << name_.c_str() << " has received " << s->Payload().c_str() << endl;
  
	}
	

  void GyroStart(){
    
  }
};

