#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include <boost/asio.hpp>
#include "chat_session.hpp"
#include"database.hpp"

using boost::asio::ip::tcp;



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
                    auto session = std::make_shared<ChatSession>(std::move(socket), sessions_, db_);
                    sessions_.push_back(session);
                    session->start();
                    
                }

                accept_connection();
            });
    }

    Database db_;
    tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<ChatSession>> sessions_;
public:
    ChatServer(boost::asio::io_context& io_context, short port)
        : db_("host=127.0.0.1 port=5432 dbname=chat_db user=postgres password=123"), acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    
    {
        accept_connection();
    }
 

    
    
   
    
};