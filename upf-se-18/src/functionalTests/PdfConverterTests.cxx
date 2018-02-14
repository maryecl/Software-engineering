#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"
#include "PdfConverter.hxx"
#include "Converter.hxx"
#include "libLibreOffice2Pdf.hxx"

class PdfConverterTests : public TestFixture<PdfConverterTests>
{
public:
  TEST_FIXTURE(PdfConverterTests)
  {
    TEST_CASE(testConvert_generateFile);
		TEST_CASE(testConvert_generateContent);
		TEST_CASE(testConvert_withInexistentOriginal);
		TEST_CASE(testConvert_polymorphicCall);
  }

  void setUp()
	{
    LibFileSystem::createNetDirectory( "config" );
		LibFileSystem::createNetDirectory( "generated" );
		LibFileSystem::createNetDirectory( "originals" );
	}
	/**
	 * The tearDown method is automatically called after each test
	 */
	void tearDown()
	{
    LibFileSystem::createNetDirectory( "config" );
		LibFileSystem::createNetDirectory( "generated" );
		LibFileSystem::createNetDirectory( "originals" );

	}
	/**
	 * This method creates files used in tests
	 */
	void createOriginalFile( const std::string & name )
	{
		std::string fullname( "originals/" );
		fullname += name;
		std::ofstream os( fullname.c_str() );
		os << "An original file" << std::endl;
		os.close();
	}

  void testConvert_generateFile(){
    PdfConverter converter;
    createOriginalFile("Original.odt");
    converter.convert("originals/Original.odt", "generated/Prefix", "printable");
    ASSERT_EQUALS(
      "generated/Prefix [printable].pdf\n",
      LibFileSystem::listDirectoryInOrder("generated")
    );
  }

  void testConvert_generateContent(){
    PdfConverter converter;
    createOriginalFile("Original.odt");
    converter.convert("originals/Original.odt", "generated/Prefix","printable");

    ASSERT_EQUALS(
      "PDF generated from 'originals/Original.odt'. Watermark: 'printable'\n",
      LibFileSystem::fileContent("generated/Prefix [printable].pdf")
    );
  }

  void testConvert_withInexistentOriginal(){
    PdfConverter converter;
    try
    {
      converter.convert("originals/Original.odt", "generated/Prefix","printable");
      FAIL( "An exception should be caught!" );
    }
    catch ( std::exception & e )
    {
      ASSERT_EQUALS(
        "The original file does not exist",
        e.what()
      )
    }
  }

  void testConvert_polymorphicCall(){

    Converter* converter = new PdfConverter(); //------------------------------
    createOriginalFile("Original.odt");
    converter->convert("originals/Original.odt", "generated/Prefix","printable");
    ASSERT_EQUALS(
      "generated/Prefix [printable].pdf\n",
      LibFileSystem::listDirectoryInOrder("generated")
    );
    delete converter;

  }






};
REGISTER_FIXTURE(PdfConverterTests)
