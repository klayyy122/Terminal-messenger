#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include<boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
using ssl_socket = boost::asio::ssl::stream<tcp::socket>;


class Client
{
private:
    boost::asio::ssl::context ssl_ctx_;
    ssl_socket socket;
    std::string read_buffer;
    std::string User_login;
    std::string User_password;

    
    void input_login();
    void input_password();
    void read();
    void write();
    void send_login_and_password();
    void send_login();
    void send_password();
    void wait_confirm_login();
    void wait_confirm_password();
    void start_chat();
    void start_chatting();

public:
    Client(boost::asio::io_context& io_context, tcp::socket&& sock)
        : ssl_ctx_(boost::asio::ssl::context::sslv23),socket(std::move(sock), ssl_ctx_)
    {   
        socket.set_verify_mode(boost::asio::ssl::verify_none);
        
    }

    void start() {
        start_handshake();
    }

    void start_handshake() {
        socket.async_handshake(boost::asio::ssl::stream_base::client,
        [this](const boost::system::error_code& ec){
            if(!ec){
                std::cout << "TLS Connection established!" << std::endl;
                input_login();
                send_login();
            } else {
                std::cerr << "Handshake failed" << ec.message() << std::endl;
            }
        });
    }

    ~Client()
    {   
        if(socket.next_layer().is_open())
            socket.next_layer().close();
    }
};