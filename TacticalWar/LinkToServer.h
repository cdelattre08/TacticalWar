#pragma once

#include <SFML/Network.hpp>

class LinkToServer
{
private:
	LinkToServer();
	~LinkToServer();
	static LinkToServer * instance;

	sf::TcpSocket socket;

	char * buffer;

	std::size_t maxRecv;
	std::size_t effRecv;
	std::size_t bufIndex;


public:
	static LinkToServer * getInstance();


	bool Connect();
	bool Disconnect();
	void Send(sf::String sContent);
	sf::String Receive();
};

