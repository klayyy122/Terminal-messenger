#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include "chat_session.hpp"
#include"database.hpp"
#include<filesystem>
#include <fstream>
#include<boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
namespace fs = std::filesystem;


class ChatServer
{
private:
    void accept_connection()
    {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    auto session = std::make_shared<ChatSession>(std::move(socket), ssl_ctx_, sessions_, db_);
                    sessions_.push_back(session);
                    session->start();
                    
                }

                accept_connection();
            });
    }
    
    Database db_;
    tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<ChatSession>> sessions_;
    boost::asio::ssl::context ssl_ctx_;
public:
    ChatServer(boost::asio::io_context& io_context, short port, std::string db_conn)
        : ssl_ctx_(boost::asio::ssl::context::sslv23), db_(db_conn), acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    
    {
        ssl_ctx_.set_options(
            boost::asio::ssl::context::default_workarounds |
            boost::asio::ssl::context::no_sslv2 |
            boost::asio::ssl::context::single_dh_use
        );

        
        ssl_ctx_.use_certificate_chain_file("server.crt");
        ssl_ctx_.use_private_key_file("server.key", boost::asio::ssl::context::pem);
        accept_connection();
    }
 

    
    
   
    
};