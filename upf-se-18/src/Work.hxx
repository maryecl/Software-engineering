#ifndef _WORK_HXX_
#define _WORK_HXX_
#include <string>
#include <iostream>
#include <cstring>
#include <memory>
#include <vector>
#include "Topic.hxx"

class Work
{
private:

	std::string _title;
	int  _isbn;
	std::string _original;
	std::string _aText;
	std::vector<Topic*> _topics;


public:
	Work(const std::string & title = "-- Untitled --",unsigned int isbn = -1,const std::string & original = "")
	{
		 _title = title;
		 _isbn = isbn;
		 _original = original;
	}
	const std::string title() const{

		return _title;
	}

	const int isbn() const{
		return _isbn;
	}

	const std::string originalFile() const{
		return _original;
	}

	const std::string aText() const{
	  std::ostringstream os ;
      os << _isbn << ", '" << _title << "', '";
      if (_original.length() > 0 ) {
		  os << "originals/";
	  }
       os << _original << "'";
      return os.str();
	}

	void title(const std::string & title){
		_title = title;
	}

	void isbn(const int & isbn){
		_isbn = isbn;
	}

	void originalFile( const std::string & originalFile){
		_original = originalFile;
	}

	void addTopic(Topic * topic){
		_topics.push_back(topic);
	}

	std::string topics(){
		std::ostringstream os;
		for(unsigned int i = 0; i < _topics.size(); i++)
			os<<"\t\t'"<<_topics[i]->name()<<"'\n";
		return os.str();
	}




};

#endif
