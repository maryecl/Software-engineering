#include "MiniCppUnit.hxx"
#include "MailStub.hxx"
#include "LibFileSystem.hxx"
#include "Channel.hxx"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>

class ChannelTests : public TestFixture<ChannelTests>
{
public:
  TEST_FIXTURE( ChannelTests )
  {
    TEST_CASE( testChannel_byDefault);
    TEST_CASE( testChannel_withOneChannel);
    TEST_CASE( testChannel_withDescriptionbyDefault);
    TEST_CASE(testChannel_newDescription);
  }


  void setUp()
  {
    LibFileSystem::createNetDirectory( "config" );
    LibFileSystem::createNetDirectory( "generated" );
    LibFileSystem::createNetDirectory( "originals" );
  }

  void tearDown()
  {
    LibFileSystem::cleanupDirectory( "config" );
    LibFileSystem::cleanupDirectory( "generated" );
    LibFileSystem::cleanupDirectory( "originals" );
    MailStub::theInstance().removeSent();
  }


  void testChannel_byDefault(){
    Channel channel;
    ASSERT_EQUALS( "No channel created", channel.name());
  }


  void testChannel_withOneChannel(){
    Channel channel;
    channel.name("Rivendel\n");
    ASSERT_EQUALS("Rivendel\n",channel.name());

  }

  void testChannel_withDescriptionbyDefault(){
      Channel channel;
      ASSERT_EQUALS( "No description", channel.description());


    }


    void testChannel_newDescription(){
      Channel channel;
      channel.description("The MeltingPot fantasy channel");
      ASSERT_EQUALS("The MeltingPot fantasy channel", channel.description());
    }


};
REGISTER_FIXTURE(ChannelTests)
