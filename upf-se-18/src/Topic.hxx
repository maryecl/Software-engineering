#ifndef Topic_hxx
#define Topic_hxx
#include <vector>
#include <fstream>
#include <string>
#include "Observer.hxx"



class Topic{

private:
  std::string _topicName;
  std::vector<Observer*> _subs;

public:

  Topic( const std::string & name = "Inexistent topic"){

    _topicName = name;
  }
  //Getter
  const std::string  name(){
    return _topicName;
  }

  //setter
  void name( const std::string & name ){
    _topicName = name;

  }

  void addSubsClient(Observer & observer){
    _subs.push_back(&observer);
  }


  std::string listSubsClients(){
    std::ostringstream os;
		for(unsigned int i = 0; i < _subs.size(); i++)
			os<<_subs[i]->name()<<"\n";
		return os.str();
  }

  void notify( const std::string & work_title, const std::string & author_name ){

    for( unsigned int i = 0; i < _subs.size(); i++ )

      _subs[i]->update( work_title, author_name );

  }

  void addSubsChannel(Observer & observer){
		_subs.push_back(&observer);
	}


};
#endif
