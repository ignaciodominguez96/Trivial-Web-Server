#include "Server.h"

unsigned int get_cant_ips_from_file(const char * filename_ips);


server::server(void)
{

}

server::server(unsigned int port) {
	
	std::cout << " Creating port " << port << " ... " << std::endl;
 
	this->IO_handler = new boost::asio::io_service();

	this->socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	
	this->server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

	std::cout << std::endl << "Ready. Port " << port << " created" << std::endl;

	this->status_error = false;
	num_actual_ip = 0;
	
	for (unsigned int i = 0; i < SIZE_EACH_IP; i++)
	{
		(this->actual_ip)[i] = NULL;
	}
	
}

server::~server() {

	(this->server_acceptor)->close();
	(this->socket_forServer)->close();
	delete (this->server_acceptor);
	delete (this->socket_forServer);
	delete (this->IO_handler);
}


bool server::is_error(void)
{
	return (this->status_error);
}

bool server::is_ip_actual_null(void)
{
	bool is_ip_null = true;

	for (unsigned int i = 0; i < SIZE_EACH_IP; i++)
	{
		if ((this->actual_ip)[i] == NULL)
		{
			is_ip_null = false;
		}
	}

	return is_ip_null;
}

char * server::get_next_ip(void)
{
	char * result = NULL;



	unsigned int cant_ips = get_cant_ips_from_file((const char *)this->filename_ips);
	
	std::ifstream ip_data((const char *)this->filename_ips);


	if ((cant_ips > 0))
	{
		if ((this->num_actual_ip == 0))
		{
			ip_data.getline(this->actual_ip, SIZE_EACH_IP);
			this->num_actual_ip++;
		}
		else if (this->num_actual_ip < this->get_ips_count())
		{


			for (unsigned int i = 0; i < this->num_actual_ip; i++)
			{
				ip_data.ignore(SIZE_EACH_IP, '\n');
			}

			ip_data.getline(this->actual_ip, SIZE_EACH_IP);

			this->num_actual_ip++;

			result = ((char *)this->actual_ip);


		}

	}
	


	return result;
}

char * server::get_message(void)
{
	return (this->buffer_message_server);
}

char server::get_letter_message(unsigned int pos)
{
	char letter;

	if (pos < SERVER_BUFFER_SIZE)
	{
		letter = (this->buffer_message_server)[pos];
	}
	else
	{
		letter = NULL;
	}

	return letter;

}

unsigned int server::get_ips_count(void)
{
	return (this->ips_count);
}

const char * server::get_filename_ips(void)
{
	return (const char *) (this->filename_ips);
}

const char * server::get_actual_ip_using(void)
{
	return (const char *)this->actual_ip;
}


void server::set_turn(unsigned int turn)
{
	this->turn = turn;
}

void server::set_status_error(bool status)
{
	this->status_error = status;
}

bool server::set_in_message_buffer(unsigned int pos, char letter)
{
	bool all_okay = true;

	if (pos < SERVER_BUFFER_SIZE)
	{
		(this->buffer_message_server)[pos] = letter;
	}
	else
	{
		all_okay = false;
	}

	return all_okay;
}

void server::set_file_ips(const char * filename)
{
	(this->filename_ips) = (char *) filename;
}





bool server::its_my_ip(const char * ip)
{
	return !(strcmp(this->actual_ip, ip));

}

void server::close_socket(void)
{
	(this->socket_forServer)->close();
}






void server::startConnection() {
	server_acceptor->accept(*socket_forServer);
	socket_forServer->non_blocking(true);
}

void server::sendMessage() {
	char buf[512] = "Hello from server.";

	size_t len;
	boost::system::error_code error;

	do
	{
		len = socket_forServer->write_some(boost::asio::buffer(buf, strlen(buf)), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}




unsigned int get_cant_ips_from_file(const char * filename_ips)
{

	std::ifstream ip_data(filename_ips);
	unsigned int cant_ips = 0;

	do {

		ip_data.ignore(SIZE_EACH_IP, '\n');
		cant_ips++;


	} while (!(ip_data.eof()));

	
	return cant_ips;
}
