#ifndef StrategySms_hxx
#define StrategySms_hxx

#include <iostream>
#include <string>

#include "MailStub.hxx"
#include "Strategy.hxx"

class StrategySms : public Strategy
{
public:

    void notification(const std::string & work_title, const std::string & author_name){
    std::string _text = "[MeltingPot] new work " + work_title + " by "+ author_name;;
    SmsStub::theInstance().sendSms( _phone,_text);
  }

};

#endif
