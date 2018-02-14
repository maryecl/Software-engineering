#ifndef StrategyWhatsapp_hxx
#define StrategyWhatsapp_hxx

#include <iostream>
#include <string>

#include "MailStub.hxx"
#include "Strategy.hxx"

class StrategyWhatsapp : public Strategy{
public:

    void notification(const std::string & work_title, const std::string & author_name){
    std::string _text = "[MeltingPot] new work " + work_title + " by "+ author_name;;
    WhatsappStub::theInstance().sendWhatsapp( _phone, _text);
  }

};

#endif
