#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include <boost/asio.hpp>
#include<boost/asio/ssl.hpp>
#include <unordered_set>
#include <unordered_map>
#include<shared_mutex>
#include <string>
#include "room.hpp"
#include"database.hpp"

using boost::asio::ip::tcp;
using ssl_socket = boost::asio::ssl::stream<tcp::socket>;
class ChatRoom;


class ISessionInterface {
public:
    virtual ~ISessionInterface() = default;
    
    virtual void leave_room() = 0;
    virtual void list_rooms() = 0;
    virtual void create_room(const std::string& name) = 0;
    virtual void join_room(const std::string& name) = 0;
    virtual void deliver(const std::string& message) = 0;
    
    virtual std::string get_login() const = 0;
};
class ChatSession : public std::enable_shared_from_this<ChatSession>, public ISessionInterface{
public:
    ChatSession(tcp::socket socket, boost::asio::ssl::context& ctx, std::vector<std::shared_ptr<ChatSession>>& sessions, Database& db)
        : socket_(std::move(socket),  ctx), sessions_(sessions), db_(db){}

    
    virtual ~ChatSession();
    
    void join_room(const std::string& room_name) override;
    void leave_room() override;
    void list_rooms() override;
    void deliver(const std::string& message);
    void create_room(const std::string& room_name) override;

    std::string get_login()  const override { return User_login;}
    std::string getLogin() const noexcept(true){
        return User_login;
    }
     std::weak_ptr<ISessionInterface> get_weak_interface() {
        return std::static_pointer_cast<ISessionInterface>(shared_from_this());
    }
    

    void start(){
        auto self(shared_from_this());
        socket_.async_handshake(boost::asio::ssl::stream_base::server, 
        [this, self](const boost::system::error_code& ec){
            if(!ec){
                authorization();
            }
            else{
                std::cerr << "TLS Handshake failed" << ec.message() << std::endl;
            }
        });
        }
   
private:

    void handle_command(const std::string& command);
    void show_help();
    void read_message();
    void write_message();
    void authorization();
    void read_login();
    void read_password();
    void send_confirm_password();
    void read_new_password();
    
    void ProcessingMessage(const std::string& msg);

    ssl_socket socket_;
    std::string read_buffer_;
    std::deque<std::string> write_msgs_;
    std::vector<std::shared_ptr<ChatSession>>& sessions_;

    std::weak_ptr<ChatRoom> current_room_;
    std::string User_login;
    std::string User_password;

    static std::unordered_set<std::string> logins_;
    static std::unordered_map<std::string, std::shared_ptr<ChatRoom>> Rooms_list;
    static std::unordered_map<std::string, std::string> registered_users_; // login -> password
    static std::unordered_set<std::string> active_users_; // currently logged in
    static std::shared_mutex rooms_mutex_;
    static std::shared_mutex users_mutex_;

    Database& db_;
};