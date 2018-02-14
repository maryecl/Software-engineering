#include "MiniCppUnit.hxx"
#include "MailStub.hxx"
#include "Work.hxx"
#include "Author.hxx"
#include "LibFileSystem.hxx"

class TopicTests : public TestFixture<TopicTests>
{
public:
	TEST_FIXTURE( TopicTests )
	{
		TEST_CASE( testTopic_byDefault );
		TEST_CASE( testTopic_newtopic);
    TEST_CASE( testWork_withOneTopic);
    TEST_CASE( testWork_withTwoTopic);
    TEST_CASE( testCatalogue_withOneTopic);
    TEST_CASE( testCatalogue_withManyTopics);

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
		LibFileSystem::cleanupDirectory( "config" );
		LibFileSystem::cleanupDirectory( "generated" );
		LibFileSystem::cleanupDirectory( "originals" );
	}
	


	void testTopic_byDefault(){
		Topic topic;
		ASSERT_EQUALS( "Inexistent topic", topic.name() );
	}

  void testTopic_newtopic(){
    Topic topic;
    topic.name("\t\tTopic\n");

    ASSERT_EQUALS("\t\tTopic\n",topic.name());
  }


  void testWork_withOneTopic(){
    Topic topic;
    topic.name("Topic 1");
    Work work;
    work.addTopic(&topic);
    ASSERT_EQUALS("\t\t'Topic 1'\n",work.topics());
  }


    void testWork_withTwoTopic(){
      Topic topic1;
      topic1.name("Topic 1");
      Topic topic2;
      topic2.name("Topic 2");
      Work work;
      work.addTopic(&topic1);
      work.addTopic(&topic2);
      ASSERT_EQUALS("\t\t'Topic 1'\n"
      "\t\t'Topic 2'\n",
      work.topics());
    }

    //Function that finds a works, and add the topic information to catalogue
    void testCatalogue_withOneTopic(){
      Author author;
      author.addWork( "A work", 111, "aFile.odt" );
      Topic topic1;
      topic1.name("Topic 1");
      author.findWork("A work").addTopic(&topic1);
      ASSERT_EQUALS("\t111, 'A work', 'originals/aFile.odt'\n"
      "\t\t'Topic 1'\n",
      author.catalogue());

    }

    //Test that find a works that has more than one topic, and adds it to cataloge
    void testCatalogue_withManyTopics(){
      Author author;
      author.addWork( "A work", 111, "aFile.odt" );
      Topic topic1;
      Topic topic2;
      topic1.name("Topic 1");
      topic2.name("Topic 2");
      author.findWork("A work").addTopic(&topic1);
      author.findWork("A work").addTopic(&topic2);
      ASSERT_EQUALS("\t111, 'A work', 'originals/aFile.odt'\n"
      "\t\t'Topic 1'\n"
      "\t\t'Topic 2'\n",
      author.catalogue());

    }




};

REGISTER_FIXTURE( TopicTests )
