#include <iostream>
#include "Client.h"

client::client(void)
{

}


client::client(const char * ip) {
	this->IO_handler = new boost::asio::io_service();
	this->socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	this->client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	this->port = 0;
}

client::~client() {
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
}


void client::set_port(const char * port)
{
	this->port =(char *) port;
}

char * client::get_port(void)
{
	return this->port;
}

void client::startConnection(const char* host) {
	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query(host, this->port));
	cout << "Trying to connect to " << host << " on port " << this->port << std::endl;
	boost::asio::connect(*socket_forClient, endpoint);
	socket_forClient->non_blocking(true);
}

void client::receiveMessage() {
	boost::system::error_code error;
	char buf[512];
	size_t len = 0;
	cout << "Receiving Message" << std::endl;
	boost::timer::cpu_timer t;
	t.start();
	boost::timer::cpu_times pastTime = t.elapsed();
	double elapsedSeconds = 0.0;
	do
	{
		len = socket_forClient->read_some(boost::asio::buffer(buf), error);

		boost::timer::cpu_times currentTime = t.elapsed();

		if ((currentTime.wall - pastTime.wall) > 1e9)
		{
			elapsedSeconds += (currentTime.wall - pastTime.wall) / 1e9;
			pastTime = currentTime;
			cout << "Pasaron " << elapsedSeconds << " segundos." << endl;
		}

		if (!error)
			buf[len] = '\0';

	} while (error.value() == WSAEWOULDBLOCK);

	if (!error)
		std::cout << std::endl << "Server sais: " << buf << std::endl;
	else
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}

