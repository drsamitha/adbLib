#include "adbLib.hpp"

using boost::asio::ip::tcp;

namespace ADB{

	ConnectionData Default = { .IPv4 = "127.0.0.1" , .port = 5037 , .timeout = 5 };

	pConnectionData overwriteDefault = &Default;

	std::string host_ = overwriteDefault->IPv4;
	int port_ = overwriteDefault->port;
	int timeout_ = overwriteDefault->timeout;

	boost::asio::io_service io_service_;
	tcp::socket socket_(io_service_);


	

	void connect() {
		tcp::resolver resolver(io_service_);
		tcp::resolver::query query(host_, std::to_string(port_));
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		boost::asio::connect(socket_, endpoint_iterator);

		socket_.set_option(boost::asio::socket_base::linger(true, 0));
		socket_.set_option(boost::asio::socket_base::keep_alive(timeout_));

		std::cout << "Connected to ADB server " << host_ << ":" << port_ << std::endl;
	}

	void close() {
		if (socket_.is_open()) {
			socket_.close();
		}
	}


	void check_status() {
		boost::array<char, 4> buf;
		boost::asio::read(socket_, boost::asio::buffer(buf));

		if (std::string(buf.data(), 4) != "OKAY") {
			std::vector<char> error_buf(1024);
			boost::asio::read(socket_, boost::asio::buffer(error_buf));
			// throw AdbConnectionError("Error: " + std::string(error_buf.data()));
		}
	}



	std::string encode_data(const std::string& msg) {
		std::ostringstream encoded;
		encoded << std::setw(4) << std::setfill('0') << std::hex << msg.size();
		
		encoded << msg;
		return encoded.str();
	}

	


	void send(const std::string& msg) {
		std::string encoded_msg = encode_data(msg);
		boost::asio::write(socket_, boost::asio::buffer(encoded_msg));
		check_status();
	}

	std::string receive() {
		boost::array<char, 4> buf;
		boost::asio::read(socket_, boost::asio::buffer(buf));
		int nob = std::stoi(std::string(buf.data(), 4), nullptr, 16);

		std::vector<char> recv_buf(nob);
		boost::asio::read(socket_, boost::asio::buffer(recv_buf));

		return std::string(recv_buf.begin(), recv_buf.end());
	}

	
}
