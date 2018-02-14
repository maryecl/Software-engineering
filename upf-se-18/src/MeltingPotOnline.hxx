#ifndef MeltingPotOnline_hxx
#define MeltingPotOnline_hxx
#include "LibFileSystem.hxx"
#include "ConverterGroup.hxx"
#include "MailStub.hxx"
#include "Topic.hxx"
#include "Client.hxx"
#include "Channel.hxx"
#include "Author.hxx"
#include "Strategy.hxx"
#include "gui/Model.hxx"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class MeltingPotOnline: public Model{

private:
	std::vector<Author*> _authors;
	std::vector<Work*> _works;
	ConverterGroup converter;
	std::vector<Topic*> _topics;
	std::vector<Client*> _clients;
	std::vector<Channel*> _channels;

public:

	MeltingPotOnline(){
		converter.add("html");
		converter.add("pdf_print");
		converter.add("pdf_mark");
		_topics.clear();
		}



	std::string catalogue() const{

		std::stringstream os;
		if(_authors.size()==0){
			os<<"";
		}
		for(unsigned int i=0; i<_authors.size();i++){
			os<<_authors[i]->contracted()<<_authors[i]->catalogue();
		}
		return os.str();
	};

//////////////////////////////////////// Author ////////////////////////////////

	//In here we create new authors and add them to the list
	void addAuthor(const std::string & author_name, bool state){
		Author* author = new Author();
		author->name(author_name);
		author->contracted(state);
		_authors.push_back(author);
	}

//we use this function to find and verify the existance of an author
Author & findAuthor(const std::string author_name)const{
	for (unsigned int i = 0; i < _authors.size(); i++) {
		if (_authors[i]->name() == author_name) {
			return *_authors[i];
		}
	}throw ExceptionFindAuthor();
}




//////////////////////////////////// Work /////////////////////////////////////

//once we find the author we add his/her works
	void addWork(const std::string & author_name, const std::string & title, int isbn,const std::string & file) {
				//we call the external function fileExists to see if the file is in originals
				if (LibFileSystem::fileExists("originals/"+file)){
					Author & author = findAuthor(author_name);
					author.addWork(title,isbn,file);
					converter.convert("originals/"+file,"generated/"+author_name+" - "+title,"printable");
					converter.convert("originals/"+file,"generated/"+author_name+" - "+title,"watermark");

				}else{
					throw ExceptionFindOriginal();
				}
	}


/////////////////////   topic   ///////////////////////////////////////////////
	void addTopic(const std::string & topic_name){

		Topic * topic = new Topic();
		topic->name(topic_name);
		_topics.push_back(topic);
	}

	std::string listTopics()const{ // We insert each topic to the list as an string

		std::stringstream os;
		for(unsigned int i = 0; i < _topics.size(); i++){
			os<< _topics[i]->name()<<"\n";
		}
		return os.str();

	}

	Topic & findTopic(const std::string topic_name)const{
		for (unsigned int i = 0; i < _topics.size(); i++){
			if (_topics[i]->name() == topic_name)
				return *_topics[i];
		}throw ExceptionFindTopic();
	}

	void associateTopicWithWork( const std::string & topic_name, const std::string & author_name,const std::string & title ){

			Topic & topic = findTopic(topic_name);
		  findAuthor(author_name).findWork(title).addTopic(&topic);
			topic.notify(title, author_name); //this way we send a mail everytime a new work is associated to a topic
	}


//////////////////////////// `Client`  ///////////////////////////////////////////

void addClient(const std::string & client_name, const  std::string & _email){

	Client * client = new Client();
	client->name(client_name);
	client->email(_email);
	_clients.push_back(client);
}


std::string listClients()const{
	std::stringstream os;
	for(unsigned int i = 0; i < _clients.size(); i++){
		os<< _clients[i]->name()<<" <"<<_clients[i]->email()<<">"<<"\n";
	}
	return os.str();

}


Client & findClient(const std::string client_name)const{
	for (unsigned int i = 0; i < _clients.size(); i++) {
			if (_clients[i]->name() == client_name)
					return *_clients[i];
	}throw ExceptionFindClient();
}


void subscribeClientToTopic(const std::string & client_name, const std::string & topic_name){

		Client & client = findClient(client_name);
		findTopic(topic_name).addSubsClient(client);

}


std::string listSubscribedToTopic(const std::string & topic_name){
	for (unsigned int i = 0; i < _topics.size(); i++){
			if (_topics[i]->name() == topic_name)
					return  _topics[i]->listSubsClients();
	}throw ExceptionFindTopic();

}


void subscribeClientToAuthor(const  std::string & client_name, const std::string  & author_name){

	Client & client = findClient(client_name);
	findAuthor(author_name).addSubsClient(client);

}

std::string listSubscribedToAuthor(const std::string & author_name){
	for (unsigned int i = 0; i < _authors.size(); i++){
			if (_authors[i]->name() == author_name)
					return  _authors[i]->listSubsClients();
	}throw ExceptionFindAuthor();

}


////////////////////////////// Channel /////////////////////////////////////////


void addChannel(const std::string &  channel_name, const std::string & description){

	Channel * channel = new Channel();
	channel->name(channel_name);
	channel->description(description);
	_channels.push_back(channel);
}


Channel & findChannel(const std::string channel_name)const{
	for (unsigned int i = 0; i < _channels.size(); i++){
		if (_channels[i]->name() == channel_name)
			return *_channels[i];
	}throw ExceptionFindChannel();
}


std::string listThematicChannels()const{
	std::stringstream os;
	for(unsigned int i = 0; i < _channels.size(); i++){
		os<< _channels[i]->name()<<"\n"<<"\t"<<_channels[i]->description()<<"\n";
	}
	return os.str();

}

std::string rssByChannel(const std::string channel_name)const{
	std::stringstream os;
	for(unsigned int i = 0; i < _channels.size(); i++){
		if (_channels[i]->name() == channel_name)
					return  _channels[i]->RSS();
	}throw ExceptionFindChannel();

}

void subscribeChannelToAuthor(const std::string & channel_name, const std::string & author_name){

	Channel & channel = findChannel(channel_name);
	Author & author = findAuthor(author_name);
	author.addSubsChannel(channel);

}
void subscribeChannelToTopic(const std::string & channel_name, const std::string & topic_name){

	Channel & channel = findChannel(channel_name);
	Topic & topic = findTopic(topic_name);
	topic.addSubsChannel(channel);

}


////////////////////////////// Notification ///////////////////////////////////

void clientPrefersSms( const std::string & client_strategy, const std::string & phone ){
	Client & client = findClient(client_strategy);
	client.phone(phone);
	client.setStrategy("SMS");
}

void clientPrefersWhatsapp( const std::string & client_strategy, const std::string & phone ){
	Client & client = findClient( client_strategy);
	client.phone(phone);
	client.setStrategy("Whatsapp");
}





//////////////////////////// Destructors ///////////////////////////////////////


	~MeltingPotOnline(){
		for( unsigned int i=0; i<_authors.size();i++){
			delete _authors[i];
		}
		for( unsigned int i=0; i<_topics.size();i++){
			delete _topics[i];
		}
		for( unsigned int i=0; i<_clients.size();i++){
			delete _clients[i];
		}
		for( unsigned int i=0; i<_channels.size();i++){
			delete _channels[i];
		}


	}

};
#endif
