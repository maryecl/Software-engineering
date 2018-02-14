#ifndef StrategyMail_hxx
#define StrategyMail_hxx

#include <iostream>
#include <string>
#include <stdio.h>

#include "MailStub.hxx"
#include "Strategy.hxx"

class StrategyMail : public Strategy
{
public:

  void notification(const std::string & work_title, const std::string & author_name){
    std::string subject = "new work " + work_title + " by "+ author_name;
    std::string to = _clientName +" <"+_email+">";
    MailStub::theInstance().sendMail(to,subject);
}

};

#endif
