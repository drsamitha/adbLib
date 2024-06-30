#include <iomanip>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <stdexcept>
#include <iostream>



namespace ADB{

// Default connectiondata  { .IPv4 = "127.0.0.1" , .port = 5037 , .timeout = 5 }
// can overwrite use overwriteDefault structure (eg;- overwriteDefault->port =5555)   
typedef struct ConnectionData{
    std::string IPv4;
    int port;
    int timeout;
}*pConnectionData;


void Connection(ConnectionData data);

void connect ();

void close();

void check_status();

void send(const std::string& msg);

std::string receive();

}