#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include <boost/asio.hpp>
#include"../config.hpp"
#include "server.hpp"

using boost::asio::ip::tcp;

int main()
{
    try
    {
        ServerConfig conf = ServerConfig::load("../config.json");

        boost::asio::io_context io_context;
        ChatServer server(io_context, conf.port, conf.db_connection);

        io_context.run();

        std::thread t([&io_context](){ io_context.run(); });

        std::cout << "Server running on port " << conf.port << std::endl;
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get();

        io_context.stop();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}