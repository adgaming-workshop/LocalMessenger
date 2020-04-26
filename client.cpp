#include <iostream>
#include <string>
#include <SFML/Network.hpp>

class Client{
public:
	std::string name;
	std::string message;
	sf::TcpSocket socket;
	sf::Packet pack;
	void connect();
	void scan();
	void registration();
	void makePack();
	void run();
};

void Client::connect(){
	if(this->socket.connect("127.0.0.1", 53000) != sf::Socket::Done){
		std::cout << "Connnection failed" << std::endl;
	//	return false;
	}
	//return true;
}

void Client::scan(){
	std::getline(std::cin, this->message);
}

void Client::registration(){
	std::getline(std::cin, this->name);
}

void Client::makePack(){
	this->pack << this->name << this->message; 
}

void Client::run(){
//	if(this->connect()){
		this->registration();
		for(;;){
			this->scan();
			this->connect();
			this->pack.clear();
			this->makePack();
			sf::Socket::Status status = this->socket.send(this->pack);
			if (status != sf::Socket::Done)
				std::cout << "Message has not been sent!" << std::endl;
			this->socket.disconnect();
		}
//	}
}

int main(){
	Client client;
	client.run();
	return 0;
}
