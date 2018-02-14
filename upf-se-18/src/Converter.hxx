#ifndef Converter_hxx
#define Converter_hxx

#include "LibFileSystem.hxx"
#include "libLibreOffice2Html.hxx"
#include "Exceptions.hxx"


class Converter{

private:


public:
	Converter( ){

	}

	virtual ~Converter(){}

	virtual void convert( const std::string & original, const std::string & generated, const std::string & mode ){};
		//method has to be implemented in chil classes


};


#endif
