#ifndef HtmlConverter_hxx
#define HtmlConverter_hxx
#include "LibFileSystem.hxx"
#include "libLibreOffice2Html.hxx"
#include "Converter.hxx"
#include <string>
#include <vector>
#include <fstream>


class HtmlConverter: public Converter {


private:

public:
HtmlConverter() {


}


void convert(const std::string  & original, const std::string & generated, const std::string & mode) {

  if (OO_WarGeneration(original.c_str(),(generated + " [multiple HTML files].war").c_str())== -1){
    throw ExceptionFindOriginal(); //OO_WarGeneration returns -1 when input file does not exist and then we throw exception

  }
}

};

#endif
