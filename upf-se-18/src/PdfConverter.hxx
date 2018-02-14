#ifndef PdfConverter_hxx
#define PdfConverter_hxx
#include "LibFileSystem.hxx"
#include "libLibreOffice2Pdf.hxx"
#include "MailStub.hxx"
#include "Converter.hxx"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


class PdfConverter: public Converter {

private:

bool watermark;

public:

PdfConverter() {

}

void convert(const std::string  & original, const std::string & generated, const std::string & mode) {

    std:: stringstream fileName;
    if (mode=="printable"){
      fileName << generated <<" [printable].pdf";
    }else{
      fileName << generated <<" [watermark].pdf";
    }
    std::string fullfile = fileName.str();

    try
      {
        LibreOfficeTools::convertToPdf(original, fullfile, mode);
      }
        catch(LibreOfficeTools::LOWriterFileNotFound)
      {
       throw ExceptionFindOriginal(); //Catches this exceptions
    }


  }

  void activateWatermark( std::string & option ){

    if( option == "activate"){
      watermark = 1;
    }else{
      watermark = 0;
    }
  }


/*}
    if( mode ="printable"){
    std::fstream pdf;
    pdf.open("generated/Prefix [printable].pdf",std::fstream::out | std::fstream::trunc);
    pdf<<"PDF generated from 'originals/Original.odt'\n";
    pdf.close();

    std::stringstream newName;
    newName <<"generated/Prefix ["<<mode<<"].pdf";
    rename("generated/Prefix [printable].pdf", newName.str().c_str() );
*/

};

#endif
