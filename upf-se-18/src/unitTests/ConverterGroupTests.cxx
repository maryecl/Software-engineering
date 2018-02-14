
#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"
#include "PdfConverter.hxx"
#include "HtmlConverter.hxx"
#include "ConverterGroup.hxx"
#include "Converter.hxx"
#include "libLibreOffice2Pdf.hxx"

class ConverterGroupTests: public TestFixture<ConverterGroupTests>
{
public:
  TEST_FIXTURE(ConverterGroupTests){

    TEST_CASE(testConvert_withHtmlConverter);
    TEST_CASE(testConvert_withoutConverter);
    TEST_CASE(testConvert_withPrintablePdfConverter);
    TEST_CASE(testConvert_withWatermarkPdfConverter);
    TEST_CASE(testConvert_withHtmlAndPdfConverters);
    TEST_CASE(testConvert_withUnknowConverter);
	}

  void setUp(){
    LibFileSystem::createNetDirectory( "config" );
		LibFileSystem::createNetDirectory( "generated" );
		LibFileSystem::createNetDirectory( "originals" );
	}
	/**
	 * The tearDown method is automatically called after each test
	 */
	void tearDown(){
    LibFileSystem::createNetDirectory( "config" );
		LibFileSystem::createNetDirectory( "generated" );
		LibFileSystem::createNetDirectory( "originals" );

	}
	/**
	 * This method creates files used in tests
	 */
	void createOriginalFile( const std::string & name ){
		std::string fullname( "originals/" );
		fullname += name;
		std::ofstream os( fullname.c_str() );
		os << "An original file" << std::endl;
		os.close();
	}


  void testConvert_withHtmlConverter(){
    ConverterGroup group;
    createOriginalFile("Original.odt");
    group.add("html");
    group.convert("originals/Original.odt", "generated/Prefix", "multiple HTML files");
    ASSERT_EQUALS(
      "generated/Prefix [multiple HTML files].war\n",
      LibFileSystem::listDirectoryInOrder("generated")
    );
  }

  void testConvert_withoutConverter(){
     ConverterGroup group;
     createOriginalFile("Original.odt"); //exception thrown when converter not found
		try
		{
			group.convert("originals/Original.odt", "generated/Prefix","multiple HTML files");
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"Converter does not exist",
				e.what()
			)
		}
	}


// CONVERSIONS TO PDF, TWO MODES
  void testConvert_withPrintablePdfConverter(){
    ConverterGroup group;
    createOriginalFile("Original.odt");
    group.add("pdf_print");
    group.convert("originals/Original.odt", "generated/Prefix", "printable");
    ASSERT_EQUALS(
      "generated/Prefix [printable].pdf\n",
      LibFileSystem::listDirectoryInOrder("generated")
    );

  }

  void testConvert_withWatermarkPdfConverter(){
    ConverterGroup group;
    createOriginalFile("Original.odt");
    group.add("pdf_mark");
    group.convert("originals/Original.odt", "generated/Prefix", "watermark");
    ASSERT_EQUALS(
      "generated/Prefix [watermark].pdf\n",
      LibFileSystem::listDirectoryInOrder("generated")
    );
  }

//converting each of the types s
  void testConvert_withHtmlAndPdfConverters(){
    ConverterGroup group;
    createOriginalFile("Original.odt");
    group.add("pdf_mark");
    group.add("pdf_print");
    group.add("html");
    group.convert("originals/Original.odt", "generated/Prefix", "watermark");
    group.convert("originals/Original.odt", "generated/Prefix", "printable");
    group.convert("originals/Original.odt", "generated/Prefix", "multiple HTML files");
    ASSERT_EQUALS(
      "generated/Prefix [multiple HTML files].war\n"
      "generated/Prefix [printable].pdf\n"
      "generated/Prefix [watermark].pdf\n",
      LibFileSystem::listDirectoryInOrder("generated")
    );
  }

  void testConvert_withUnknowConverter(){
  ConverterGroup group;
   try
   {
     group.add("undef"); //There is no type defined as undef so the exception is thrown
     FAIL( "An exception should be caught!" );
   }
   catch ( std::exception & e )
   {
     ASSERT_EQUALS(
       "Unsopported format",
       e.what()
     )
   }
 }







};
REGISTER_FIXTURE(ConverterGroupTests)
