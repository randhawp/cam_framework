#include <iostream>
#include <map>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include "./includes/events.h"
#include "./includes/eventmanager.h"

#include "./includes/camera.h"
#include "./includes/webserver.h"
#include "./includes/gyro.h"
#include "./includes/M0.h"
using namespace std;


namespace {
  using namespace std::placeholders;
  template<class TP,class TS>
	long Subscribe(TP& publisher, TS& subscriber) {
		return publisher->Register(bind(&TS::OnEventReceived, &subscriber, _1, _2));
	}
  template<class TP>
	void Unsubscribe(TP& publisher, long token) {
		publisher->Unregister(token);
	}
}

int main() {
  
  //init the services webserver, camera, gyro, m0 etc
  shared_ptr<Webserver> web(new Webserver("webserver"));
  std::thread webth([web](){
    web->Webserver::ServerStart();
    
  });

  shared_ptr<Camera> cam(new Camera("Camera"));
	std::thread camth([cam](){
    cam->Camera::takesomepics();
    
  });

  shared_ptr<M0>  m0(new M0("Mzero"));
  std::thread m0th([m0](){
    m0->M0::Check_mo_msg();
    
  });
  
  Gyro gyro("gyroscope");
  
  // define the communication map
	
	Subscribe(cam, *web); //webserver recv from cam
  Subscribe(web, *cam); //cam recv from webserver
  Subscribe(web, gyro); //gyro recv from webserver
  Subscribe(m0, *web); // webserver recv from m0
  
  
  webth.join();
  m0th.join();
  camth.join();
	return 0;
}