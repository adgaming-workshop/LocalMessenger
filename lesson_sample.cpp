// Client:

#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>

int main()
{
    sf::TcpSocket socket;
    
    if (socket.connect("127.0.0.1", 53000) != sf::Socket::Done)
    {
        std::cout << "Connection failed" << std::endl;
        return 0;
    }

    for (;;)
    {
        char data[] = "THIS IS MY MESSAGE FROM CLIENT";
        sf::Socket::Status status = socket.send(data, strlen(data) + 1);

        if (status == sf::Socket::Done) {
            std::cout << "Msg has been sent successfully" << std::endl;
        } else {
            std::cout << "Msg has been sent unsuccessfully" << std::endl;
        }
    }
    


    return 0;
}

// Server:

#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>

int main()
{
    sf::TcpListener listener;

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
            char data[10] = {};
            std::size_t bytesReceived = 0;

            std::cout << "Waiting for receive" << std::endl;
            sf::Socket::Status status = socket.receive(data, 10, bytesReceived);

            if (status == sf::Socket::Done)
            {
                std::cout << "Got " << bytesReceived << " bytes." << std::endl;
                std::cout << "Msg: " << data << std::endl;
            }

            if (status == sf::Socket::Disconnected)
            {
                std::cout << "Client disconnected" << std::endl;
                break;
            }
        }
    }

    return 0;
}
