#ifndef SERVER_H
#define SERVER_H


#include <iostream>
#include <fstream>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>


#define SERVER_BUFFER_SIZE 512
#define SIZE_EACH_IP 16

class server {


public:
	server(void);
	server(unsigned int port);
	~server();

	bool is_error(void);
	bool is_ip_actual_null(void);

	char * get_message(void);
	char get_letter_message(unsigned int pos);
	unsigned int get_ips_count(void);
	const char * get_filename_ips(void);
	char * get_next_ip(void);
	const char * get_actual_ip_using(void);

	void set_turn(unsigned int turn);
	void set_status_error(bool status);
	bool set_in_message_buffer(unsigned int pos, char letter);
	void set_file_ips(const char * filename);



	bool its_my_ip(const char * ip);
	void close_socket(void);

	

	void startConnection();
	void sendMessage();
	

private:

	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;

	bool status_error;

	unsigned int turn;
	unsigned int ips_count;

	unsigned int num_actual_ip;
	char actual_ip[SIZE_EACH_IP];
	char buffer_message_server[SERVER_BUFFER_SIZE];
	
	char * filename_ips;

	

};





#endif // !SERVER_H



