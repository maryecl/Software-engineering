#ifndef Channel_hxx
#define Channel_hxx
#include <string>
#include "Observer.hxx"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>

class Channel:public Observer{
  typedef struct{
    std::string work_title;
    std::string author_name;
  }notifs;

private:
  std::string  _channel;
  std:: string _description;
  std:: string _rss;
  bool notif;
  notifs _notification;
  std::vector<notifs*> _notifications;

public:
  Channel(const std::string & name = "No channel created", const std::string & description = "No description"){
    _channel = name;
    _description = description;
    notif = false;
  }

//getter
  const std::string  name(){
    return _channel;
  }

//setter
  void name(const std::string & name){
    _channel = name;
  }

//Getter
  const std::string  description(){
    return _description;
  }
//setter
  void description(const std::string & description){
    _description = description;
  }


    std::string RSS(){
    std::ostringstream os;
    os<<	"<?xml version='1.0' encoding='UTF-8' ?>\n"
			"<rss version='2.0'>\n"
			"<channel>\n";
		os<<"<title>MeltingPotOnline: "<<_channel<<"</title>\n"
			"<link>http://www.meltingpotonline.com/"<<_channel<<"</link>\n";
		os<<"<description>"<<_description<<"</description>\n";
    for(unsigned int i =0; i<_notifications.size();i++){
      if(notif){
        os<<"<item>\n";
  			os<<"<title>Novelty: '"<<_notifications[i]->work_title<<"' by '"<<_notifications[i]->author_name<<"'</title>\n";
  			os<<"<link>http://www.meltingpotonline.com/infoWork?author='"<<_notifications[i]->author_name<<"'&title='"<<_notifications[i]->work_title<<"'</link>\n";
  			os<<"</item>\n";
      }
    }
			os<<"</channel>\n"
			"</rss>\n";

    return _rss = os.str();

  }

  void update( const std::string & work_title, const std::string & author_name){
    notif = true;
    notifs* notification = new notifs;
    notification->work_title = work_title;
    notification->author_name = author_name;
    _notifications.push_back(notification);

}


////////////////////////////////// Destructor /////////////////////////////////

~Channel(){
  for( unsigned int i=0; i<_notifications.size();i++){
    delete _notifications[i];
  }

}

};

#endif
