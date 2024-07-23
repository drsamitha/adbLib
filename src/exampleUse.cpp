/**
 * @example
 * @file exampleUse.cpp
 * @brief Example program demonstrating the usage of the adbLib library.
 *
 * This program showcases how to communicate to an Android device using adbLib,
 * send commands, receive responses, and execute shell commands.
 */

#include "adbLib.hpp"

/**
 * @brief Main function of the example program.
 *
 * This function demonstrates the basic functionalities of the adbLib library.
 * It connects to an adb server, sends commands, receives responses,
 * and executes shell commands etc.
 *
 * @return 0 if the program runs successfully, non-zero otherwise.
 */	
int main() {
	try {
		/**
		 * @code 
		 * ADB::ConnectionData dt = { .IPv4 = "127.0.0.1" , .port = 5555 , .timeout = 5 };
		 * @endcode
		 * @brief Connection data for the ADB connection.
		 *
		 * This structure holds the IP address, port, and timeout for the ADB connection.
		 */
		ADB::ConnectionData dt = { .IPv4 = "127.0.0.1" , .port = 5555 , .timeout = 5 };

		/**
		 * @code 
		 * ADB::connect(dt);
		 * @endcode
		 * @brief Connect to the ADB server using default settings.
		 *
		 * This function establishes a connection to the ADB server using the default settings.
		 */
		ADB::connect(ADB::Default);

		/**
		@code 
		 * ADB::send("host:devices");
		 * @endcode
		 * @brief Send a command to the ADB server.
		 *
		 * This function sends the specified command to the ADB server.
		 *
		 * @param command The command to send.
		 */
		ADB::send("host:devices");

		/**
		 * @code 
		 * std::string devices = ADB::receive();
		 * std::cout << "Received: " << devices << std::endl;
		 * @endcode
		 * @brief Receive a response from the ADB server.
		 *
		 * This function receives the response from the ADB server.
		 *
		 * @return The received response as a string. for here attached devices details
		 */
		std::string devices = ADB::receive();
		std::cout << "Received: " << devices << std::endl;

		/**
		 * @code 
		 * ADB::close();
		 * @endcode
		 * @brief Close the ADB connection.
		 *
		 * This function closes the connection to the ADB server.
		 */
		ADB::close();

		/**
		 * @code 
		 * ADB::connect(dt);
		 * @endcode
		 * @brief Connect to the ADB server using custom connection data.
		 *
		 * This function establishes a connection to the ADB server using the specified connection data.
		 *
		 * @param data The connection data to use.
		 */
		ADB::connect(dt);

		/**
		 * @code 
		 * ADB::send("host:transport-any");
		 * @endcode
		 * @brief Send a command to transport connection of the ADB server.
		 *
		 * This function sends the specified command to the ADB server.
		 *
		 * @param command The command to transport.
		 */
		ADB::send("host:transport-any");

		/**
		 * @code 
		 * ADB::shell("uname")
		 * @endcode
		 * @brief Execute a shell command on the Android device.
		 *
		 * This function executes the specified shell command on the Android device.
		 *
		 * @param command The shell command to execute.
		 */
		ADB::shell("uname");

		/**
		 * @code 
		 * std::string shhl = ADB::shell_result();
		 * std::cout << "Received: " << shhl << std::endl;
		 * @endcode
		 * @brief Get the result of the last executed shell command.
		 *
		 * This function retrieves the result of the last executed shell command.
		 *
		 * @return The result of the shell command as a string.
		 */
		std::string shhl = ADB::shell_result();
		std::cout << "Received: " << shhl << std::endl;

		ADB::close();

	}
	catch (const std::exception& e) {
		std::cerr << "error : " << e.what() << std::endl;
	}

	return 0;
}
