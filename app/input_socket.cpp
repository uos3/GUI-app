#include "input_socket.h"

#include "utility.h"

#include <QAbstractSocket>
#include <QHostAddress>
#include <QIODevice>

#include <algorithm>


SocketInputClient::SocketInputClient (QTcpSocket* socket,
                                      QObject* parent)
	: QObject(parent), socket(socket) {

	connect(socket, &QIODevice::readyRead,
	        this, &SocketInputClient::new_data);
	connect(socket,
	        QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
	        [](QAbstractSocket::SocketError error){
		qWarning("Encountered socket error %i for a socket data input.", error);
	});

}

void SocketInputClient::new_data () {
	QByteArray read = socket->readAll();

	// get the data from the QByteArray, such that we own it. unfortunately, I can't
	// see a way to do this other than to copy it out.
	std::unique_ptr<char[]> data(new char[read.size()]);
	std::copy(read.data(), read.data() + read.size(), data.get());
	Buffer buffer(std::move(data), read.size());

	Packet packet;
	from_buffer(packet, buffer, util::now());

	emit new_packet(buffer, packet);
}

QTcpSocket* SocketInputClient::get_socket () {
	return socket;
}


SocketInput::SocketInput (uint16_t port,
                          const std::string& hostname,
                          QObject *parent)
	: Input(parent)
	, socket(this) {

	socket.listen(QHostAddress(QString::fromStdString(hostname)), port);

	connect(&socket, &QTcpServer::newConnection, this, &SocketInput::new_client);
}

void SocketInput::new_client () {
	auto client = new SocketInputClient(socket.nextPendingConnection(), this);
	clients.push_back(client);

	connect(client, &SocketInputClient::new_packet,
	        this, &SocketInput::new_packet);

	connect(client->get_socket(), &QTcpSocket::disconnected, [&](){
		clients.erase(
			std::remove(clients.begin(), clients.end(), client), clients.end());
	});
}
