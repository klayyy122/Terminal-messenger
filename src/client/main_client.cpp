#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include"../config.hpp"
#include "client.hpp"



int main() 
{
    try 
    {   ClientConfig conf = ClientConfig::load("../config.json");
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        socket.connect(tcp::endpoint(boost::asio::ip::make_address(conf.ip), conf.port));

        auto c = std::make_shared<Client>(io_context, std::move(socket));
        c->start();
        io_context.run();
    } 
    catch (std::exception& e) 
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}