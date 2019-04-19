#include "Client.h"
#include "Server.h"


void TCPserver(server * server, client * client);
void asioTcpClient(client * conquering, const char* host);

int main(int argc, char* argv[])
{
	server server1;
	server1 = server();

	client client1;
	client1 = client();


	TCPserver(&server1, &client1);
	asioTcpClient(&client1, SERVER_IP);
	std::cout << "Press Enter to exit..." << std::endl;
	getchar();
}


void TCPserver(server * server, client * client)
{

	std::cout << std::endl << "Start Listening on port " << server->get_actual_ip_using() << std::endl;
	server->startConnection();
	std::cout << "Somebody connected to port " <<  client->get_port() << std::endl;
	std::cout << "Press Enter to Send Message  " << std::endl;
	getchar();
	server->sendMessage();
	Sleep(50); // Le damos 50ms para que llegue el mensaje antes de cerrar el socket.
}

void asioTcpClient(client * conquering, const char* host)
{
	conquering->startConnection(host);
	conquering->receiveMessage();

}