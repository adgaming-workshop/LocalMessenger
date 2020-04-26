#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>

class MessageServer{ 
	public:
		sf::TcpListener listener;
		sf::TcpSocket message_socket; //FOR LAST MESSAGE TO UPDATE, CURRENT CONNECTION
		sf::TcpSocket chat_socket; //WHOLE CHAT
		std::string current_name;
		std::string current_message;
		void startServer();
		void connect();
		void manage();
		void sendUpdates();
	};

void MessageServer::startServer(){
	if (this->listener.listen(53000) != sf::Socket::Done){
		std::cout << "Can't bind the port" << std::endl;
		return;
	}
	std::cout << "Server has been started working." << std::endl;
}

void MessageServer::connect(){
	 if (this->listener.accept(this->message_socket) != sf::Socket::Done) {
            std::cout << "Can not accept connection" << std::endl;
            return;
        }
}

void MessageServer::manage(){
	this->connect();    
	for(;;){
		sf::Packet data;
            
                sf::Socket::Status status = this->message_socket.receive(data);

            if (status == sf::Socket::Done)
            {
                data >> this->current_name >> this->current_message;
                std::cout << this->current_name << ": " << this->current_message << std::endl;
		//this->message_socket.disconnect();
            }

            if (status == sf::Socket::Disconnected)
            {
                std::cout << "Client disconnected" << std::endl;
                break;
            }
	    }
}
	    
void MessageServer::sendUpdates(){
	sf::Packet posylka;
	posylka << this->current_name << this->current_message;
	chat_socket.send(posylka);

}

int main()
{
    /*sf::TcpListener listener;

    if (listener.listen(53000) != sf::Socket::Done) 
    {
        std::cout << "Can not binding port" << std::endl;
        return 0;
    }

    for (;;)
    {
        sf::TcpSocket socket;
        if (listener.accept(socket) != sf::Socket::Done) {
            std::cout << "Can not accept connection" << std::endl;
            return 0;
        }

        std::cout << "Client connected" << std::endl;

        for (;;)
        {
            //char data[10] = {};
		sf::Packet data;
            std::size_t bytesReceived = 0;

            std::cout << "Waiting for receive" << std::endl;
            sf::Socket::Status status = socket.receive(data);

            if (status == sf::Socket::Done)
            {
                std::cout << "Got " << bytesReceived << " bytes." << std::endl;
		std::string message;
		data >> message;
                std::cout << "Msg: " << message << std::endl;
            }

            if (status == sf::Socket::Disconnected)
            {
                std::cout << "Client disconnected" << std::endl;
                break;
            }
        }
    }

    return 0; */

	MessageServer server;
	server.startServer();
	for (;;){
		server.manage();
	}


}































