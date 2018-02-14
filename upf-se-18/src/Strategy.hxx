#ifndef Strategy_hxx
#define Strategy_hxx
#include "MailStub.hxx"
#include<iostream>
#include <stdio.h>

class Strategy{

protected:

  std::string _clientName;
  std::string _email;
  std::string _phone;

public:


  virtual void notification(const std::string & work_title, const std::string & author_name)= 0;

  void name( const std::string & name ){
    _clientName = name;

  }
  void phone( const std::string & phone ){
    _phone = phone;
  }
  void email( const std::string & email ){
    _email = email;
  }

  virtual ~Strategy(){}

};
#endif
