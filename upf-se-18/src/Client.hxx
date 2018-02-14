#ifndef Client_hxx
#define Client_hxx
#include <vector>
#include <fstream>
#include "MailStub.hxx"
#include "Observer.hxx"
#include "Strategy.hxx"
#include "StrategyMail.hxx"
#include "StrategySms.hxx"
#include "StrategyWhatsapp.hxx"
#include <string>


class Client:public Observer{

private:

  std::string _clientName;
  std::string _email;
  std::string _phone;
  Strategy * _strategy;


public:

  Client(const std::string & name = "No clients", const std::string & email = "No email"){
    _clientName = name;
    _email = email;
    _strategy = new StrategyMail();
  }

  //Getter name
  const std::string name(){
    return _clientName;

  }

  //setter name
  void name( const std::string & name ){
    _clientName = name;
    _strategy->name(_clientName);

  }

  //Getter email
  const std::string email(){
    return _email;

  }

  //setter email
  void email( const std::string & email ){
    _email = email;
    _strategy->email(_email);
  }

  const std::string phone(){
    return _phone;
  }


  void phone( const std::string & phone ){
    _phone = phone;
    _strategy->phone(_phone);

  }



//notifies mailStub to send a mail
void update( const std::string & work_title,  const std::string & author_name){
    _strategy->notification(work_title, author_name);
}


void setStrategy(const std::string & strat){
    delete _strategy;
    if ( strat == ("SMS")){
       _strategy = new StrategySms();
    }else if(strat == ("Whatsapp")){
        _strategy = new StrategyWhatsapp();
    }else{
        _strategy = new StrategyMail();
    }
    _strategy->name(_clientName);
    _strategy->email(_email);
    _strategy->phone(_phone);
  }

~Client(){
  delete _strategy;
}
};
#endif
