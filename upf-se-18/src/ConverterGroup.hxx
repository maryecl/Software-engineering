#ifndef ConverterGroup_hxx
#define ConverterGroup_hxx
#include "LibFileSystem.hxx"
#include "libLibreOffice2Pdf.hxx"
#include "Converter.hxx"
#include "PdfConverter.hxx"
#include "HtmlConverter.hxx"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


class ConverterGroup{

private:
std::vector<Converter *> _converters;
HtmlConverter converter;



public:
  ConverterGroup(){
  }
  void add(const std::string & model) {
    Converter * converter = NULL;
    if (model == "html") {
      converter = new HtmlConverter();
    } else if(model == "pdf_print" || model == "pdf_mark") {
      converter =  new PdfConverter();
    }else{
      throw ExceptionUnsupported();
    }
    _converters.push_back(converter);
  }

  void convert(const std::string  & original, const std::string & generated, const std::string & mode) {

    if (_converters.size() == 0) {
      throw ExceptionFindConverter();
    } else {
      for (unsigned int i = 0; i < _converters.size(); i++) {
            _converters[i]->convert(original, generated, mode);

      }
    }
  }



  ~ConverterGroup(){
    for( unsigned int i=0; i<_converters.size();i++){
      delete _converters[i];
    }
  }


};

#endif
