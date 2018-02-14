#ifndef Observer_hxx
#define Observer_hxx

#include <iostream>
#include <string>

//Observer pattern, this is an abstract class and the classes wich inherit will have to implemente the methods
class Observer{
public:
  Observer(){}
  virtual const std::string name()=0;
  virtual void update( const std::string & work_title, const std::string & author_name)=0;
  virtual ~Observer(){}
};
#endif
