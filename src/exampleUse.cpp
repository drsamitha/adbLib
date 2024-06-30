
#include "adbLib.hpp"


int main() {
	
    try {
		
        ADB::connect();
		// ADB::send("host:devices");
		// std::string devices = ADB::receive();
		// std::cout << "Received: " << devices << std::endl;
		ADB::close();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}