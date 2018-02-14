#include "MiniCppUnit.hxx"
#include "MailStub.hxx"
#include "LibFileSystem.hxx"
#include "Client.hxx"

class ClientTests : public TestFixture<ClientTests>
{
public:
  TEST_FIXTURE( ClientTests )
  {
    TEST_CASE( testClient_byDefault );
    TEST_CASE( testClient_newClient);
    TEST_CASE( testClient_emailByDefault);
    TEST_CASE( testClient_newEmail);
    TEST_CASE( testClient_updatesubscription);
  }


  void tearDown()
  {
    LibFileSystem::cleanupDirectory( "config" );
    LibFileSystem::cleanupDirectory( "generated" );
    LibFileSystem::cleanupDirectory( "originals" );
    MailStub::theInstance().removeSent();
  }

  void testClient_byDefault (){
    Client client;
    ASSERT_EQUALS( "No clients", client.name());
  }

  //we give a name to a new client
  void testClient_newClient(){
    Client client;
    client.name("A client");
    ASSERT_EQUALS("A client", client.name());
  }

  void testClient_emailByDefault(){
    Client client;
    ASSERT_EQUALS( "No email", client.email());
  }

  void testClient_newEmail(){
    Client client;
    client.email("a@mail.org");
    ASSERT_EQUALS("a@mail.org", client.email());
  }

//Test created to be able to send notifications to clients and use MailStub

  void testClient_updatesubscription(){
    Client client;
    client.name("A client");
    client.email("a@mail.org");
    client.update("A work", "An author");
    ASSERT_EQUALS(
      "To: A client <a@mail.org>\n"
      "Subject: new work A work by An author\n"
      "\n",
      MailStub::theInstance().sentMails()
    );
}





};
REGISTER_FIXTURE( ClientTests )
