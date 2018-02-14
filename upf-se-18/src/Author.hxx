#ifndef Author_hxx
#define Author_hxx
#include "Work.hxx"
#include "Exceptions.hxx"
#include "MailStub.hxx"
#include "Observer.hxx"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>




class Author{

	private:

	std::string _name;
	bool _isContracted;
	std::vector<Work *> _works;
	std::vector <Observer*> _subs;


	public:

	Author(const std::string & name = "-- NoName --", bool isContracted = false){
		_name = name;
		_isContracted = isContracted;
		//_catalogue = "";
		//count = 0;
	}

	const std::string  name(){
		return _name;
	}

	bool isContracted(){
		return _isContracted;
	}

	void contracted(bool state ){
		_isContracted = state;
	}


	void name(const std::string & name){
		_name = name;

	}

	void contract(){
		_isContracted = true;
	}

	void nocontract(){
		_isContracted = false;
	}


	/*---------------------------P2-------------------------------*/



	std::string catalogue() {

			std::stringstream os;
			os<<"";
			for(unsigned int i = 0; i<_works.size(); i++){
				os<<"\t"<<_works[i]->isbn()<<", '";
				os<< _works[i]->title()<<"', "<<"'originals/";
				os<< _works[i]->originalFile()<<"'\n";
				os<< _works[i]->topics();
			}

			return os.str();

}

void addWork(const std::string & title, unsigned int isbn, const std::string & file){

		 Work *work = new Work();
		 work->title(title);
		 work->isbn(isbn);
		 work->originalFile(file);
		 notify(title);
		_works.push_back(work);
}


Work & findWork(const std::string &title){
	for(unsigned int i=0; i<_works.size(); i++){
		//if(((_works[i]->title()).compare(title)) == 0){
		if( _works[i]->title() == title ){
			return *_works[i];
		}

	} throw ExceptionFindWork();

}

std::string contracted() const{

	if(_isContracted == true){
		return _name + " [contracted]\n";
	}else{
		return _name + " [external]\n";
	}

}


std::string description() {
		std::stringstream os;

		os<< contracted();
		if (_works.size() > 0) {
			for (unsigned int i = 0; i < _works.size(); i++) {
				os << "\t" << _works[i]->isbn() << ", '" << _works[i]->title() << "', 'originals/" << _works[i]->originalFile() << "'\n" ;
			}
		}

		return os.str();
	}

////////////////////   This functions are used to notify the  users subscribed to a certain author  /////////////////////////////////////////////

	void addSubsClient(Observer & observer){
		_subs.push_back(&observer);
}

	std::string listSubsClients(){
		std::ostringstream os;
		for(unsigned int i = 0; i < _subs.size(); i++)
			os<<_subs[i]->name()<<"\n";
		return os.str();
	}

	void notify( const std::string & work_title){

    for( unsigned int i = 0; i < _subs.size(); i++ )
      _subs[i]->update( work_title, _name);

  }


	///////////////////// suscribed Channels /////////////////////////////////////

	void addSubsChannel(Observer & observer){
		_subs.push_back(&observer);
	}


	~Author(){
		for( unsigned int i=0; i<_works.size();i++){
			delete _works[i];
		}
	}

};
#endif
