#ifndef _COLLECTION_HXX_
#define _COLLECTION_HXX_
#include "Author.hxx"
#include <vector>
#include <string>


class Collection {

private:

		std::string _title;
		bool _published;
		std::vector <Work*> _works;



public:
	Collection(const std::string & title = "-- Untitled --", bool published = false)
	{
		_title = title;
		_published = published;
	}


	void addWork(Work & work){
			 _works.push_back(&work);
	}


	const std::string title() const{
		return _title;
	}

	const bool isPublished() const{
		return _published;
	}

	void publish() {
		_published = true;
	}

	void withdraw() {
		_published = false;
	}

	void title(const std::string & title){
		_title = title;
	}

std::string workList(){
	std::stringstream os;

	os << "";

	if (_works.size() > 0) {
		for (unsigned int i = 0; i < _works.size(); i++) {
			//os << i+1 << ": " << _works[i].isbn() << ", '" << _works[i].title() << "', 'originals/" << _works[i].originalFile() << "'\n" ;
			os << i+1 << ": " << _works[i]->isbn() << ", '" << _works[i]->title() << "', 'originals/" << _works[i]->originalFile() << "'\n" ;
		}
	}


		return os.str();

	}
};

#endif
