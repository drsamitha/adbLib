#include <iomanip>
#include <iostream>


/**
 * @namespace ADB
 * @brief Namespace for ADB library functions.
 */
namespace ADB{

    /**
     * @struct ConnectionData
     * @brief Structure containing connection data for ADB.
     * 
     * @param IPv4 The IPv4 address of the ADB server. Default is "127.0.0.1".
     * @param port The port number of the ADB server. Default is 5037.
     * @param timeout The timeout in seconds for ADB operations. Default is 5.
     * 
     * @note The default connection data can be overwritten using a ConnectionData structure.
     * 
     * @example
     * ```cpp
     * ADB::ConnectionData overwriteDefault = { .IPv4 = "192.168.1.10" , .port = 5037 , .timeout = 5 };
     * 
     * ADB::connect(overwriteDefault);
     * ```
     */
typedef struct ConnectionData{
    std::string IPv4 ;
    int port ;
    int timeout ;
}*pCD;

ConnectionData Default = { .IPv4 = "127.0.0.1" , .port = 5037 , .timeout = 5 };



    /**
     * @brief Connects to the ADB server.
     * 
     * @note This function should be called to establish a connection.
     */
void connect (const ConnectionData& Default);





    /**
     * @brief Closes the connection to the ADB server.
     */
void close();




    /**
     * @brief Checks the status of the ADB connection.
     */
void check_status();




    /**
     * @brief Sends a message to the ADB server.
     * 
     * @param msg The message to send.
     */
void send(const std::string& msg);




    /**
     * @brief Receives a message from the ADB server.
     * 
     * @return The received message.
     */
std::string receive();




    /**
     * @brief Sends a message to the ADB shell.
     * 
     * @param msg The message to send.
     */
void shell(const std::string& cmd);




    /**
     * @brief Receives a result from the ADB shell.
     * 
     * @return The received message if any.
     */
std::string shell_result();

}