#include "MiniCppUnit.hxx"
#include "Author.hxx"
#include "MailStub.hxx"
#include "LibFileSystem.hxx"

class AuthorTests : public TestFixture<AuthorTests>
{
	public:
	TEST_FIXTURE( AuthorTests )
	{
		TEST_CASE( testName_byDefault );
		TEST_CASE( testName_addingName);
		TEST_CASE( testContract_byDefault);
		TEST_CASE( testContract_isContracted);
		TEST_CASE( testContract_notContracted);
	}


	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "config" );
		LibFileSystem::cleanupDirectory( "generated" );
		LibFileSystem::cleanupDirectory( "originals" );
	}

	void testName_byDefault()
	{
		Author author;
		ASSERT_EQUALS( "-- NoName --", author.name() );
	}


	void testName_addingName()
	{
		Author author;
		author.name( "A name" );
		ASSERT_EQUALS( "A name", author.name() );
	}

	void testContract_byDefault()
	{
		Author author;
		ASSERT_EQUALS(false, author.isContracted());

	}


	void testContract_isContracted()
	{
		Author author;
		author.contract();
		ASSERT_EQUALS( true, author.isContracted() );

	}

	void testContract_notContracted()
	{
		Author author;
		author.contract();
		author.nocontract();
		ASSERT_EQUALS(false, author.isContracted() );

	}


};
REGISTER_FIXTURE( AuthorTests )
