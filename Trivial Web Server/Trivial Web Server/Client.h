
#ifndef CLIENT_H
#define CLIENT_H


#include <cstdio>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>

#define HELLO_PORT_STR "50013"
#define SERVER_IP "localhost"

using namespace std;

class client {
public:
	client(void);
	client(const char * ip);

	void set_port(const char * port);
	char * get_port(void);

	void startConnection(const char* host);
	void receiveMessage();
	~client();

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	char * port;
};


#endif // !CLIENT_H