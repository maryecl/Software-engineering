#ifndef Exception_hxx
#define Exception_hxx

#include <iostream>
#include <string>

class ExceptionFindWork : public std::exception
{
public:
	const char* what() const throw ()
	{
		return "The work does not exist";
	}
};

class ExceptionFindAuthor : public std::exception{

public:
		const char* what() const throw(){
			return "The author does not exist";
		}
};

class ExceptionFindOriginal : public std::exception{

public:
	const char* what() const throw(){
		return "The original file does not exist";
	}
};

class ExceptionFindConverter : public std::exception{

public:
	const char* what() const throw(){
		return "Converter does not exist";
	}
};

class ExceptionUnsupported: public std::exception{

public:
	const char* what() const throw(){
		return "Unsopported format";
	}
};


class ExceptionFindTopic: public std::exception{
	public:
		const char* what() const throw(){
			return "The topic does not exist";
		}
};

class ExceptionFindClient: public std::exception{
	public:
		const char* what() const throw(){
			return "The client does not exist";
		}
};


class ExceptionFindChannel: public std::exception{
	public:
		const char* what() const throw(){
			return "The thematic channel does not exist";
		}
};




#endif
