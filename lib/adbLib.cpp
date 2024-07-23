#include "adbLib.hpp"

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <stdexcept>


using boost::asio::ip::tcp;

namespace ADB{
	

		boost::asio::io_service io_service_;
		tcp::socket socket_(io_service_);


	void connect(const ConnectionData& Default) {
		
		
			std::string host_ = Default.IPv4;
			int port_ = Default.port;
			int timeout_ = Default.timeout;


		tcp::resolver resolver(io_service_);
		tcp::resolver::query query(host_, std::to_string(port_));
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		boost::asio::connect(socket_, endpoint_iterator);

		socket_.set_option(boost::asio::socket_base::linger(true, 0));
		socket_.set_option(boost::asio::socket_base::keep_alive(timeout_));

		
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
			std::cout << "FAIL " << std::endl;
			std::cout << "Error: " << std::string(error_buf.begin(), error_buf.end()) << std::endl;
		
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




	void shell(const std::string& cmd){
				
		std::stringstream ss;
		ss << "shell:" << cmd;
		std::string full_cmd = ss.str();
		
		send(full_cmd);
	}




	std::string shell_result() {
        boost::asio::streambuf buffer;
        boost::system::error_code error;

        // Read until the connection is closed by the server
        boost::asio::read(socket_, buffer, error);

        // If the connection was closed, error would be eof
        if (error != boost::asio::error::eof) {
            throw boost::system::system_error(error); // Handle other errors
        }

        // Convert the streambuf to a string
        std::istream is(&buffer);
        std::string response((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
        
        return response;
    }

	
}
