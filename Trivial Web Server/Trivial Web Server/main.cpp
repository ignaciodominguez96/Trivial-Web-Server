#include "Client.h"
#include "Server.h"

void TCPserver(void);
void asioTcpClient(const char* host);

int main(int argc, char* argv[])
{
	server server1();
	client client1();

	TCPserver();
	asioTcpClient(SERVER_IP);
	std::cout << "Press Enter to exit..." << std::endl;
	getchar();
}


void TCPserver()
{
	server conquering;
	std::cout << std::endl << "Start Listening on port " << HELLO_PORT << std::endl;
	conquering.startConnection();
	std::cout << "Somebody connected to port " << HELLO_PORT << std::endl;
	std::cout << "Press Enter to Send Message  " << std::endl;
	getchar();
	conquering.sendMessage();
	Sleep(50); // Le damos 50ms para que llegue el mensaje antes de cerrar el socket.
}

void asioTcpClient(const char* host)
{
	client conquering;
	conquering.startConnection(host);
	conquering.receiveMessage();

}