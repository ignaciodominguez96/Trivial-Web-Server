#pragma once

#ifndef SERVER_H
#define SERVER_H



#include <iostream>
#include <cstdio>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#define HELLO_PORT 50013

class server {
public:
	server();
	void startConnection();
	void sendMessage();
	void writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes);
	~server();

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
};





#endif // !SERVER_H



