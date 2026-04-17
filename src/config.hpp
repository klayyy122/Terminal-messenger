#include<iostream>
#include<fstream>
#include<filesystem>
#include<nlohmann/json.hpp>
namespace fs = std::filesystem;

struct ServerConfig {
    int port;
    std::string db_connection;

    static ServerConfig load(const std::string& filename) {
        if(!fs::exists(filename) ||  fs::path(filename).extension() != ".json") {
            throw std::runtime_error("not correct config file or it does not exist");
        }
        std::ifstream file(filename);
        nlohmann::json js;
        file >> js;

        return ServerConfig {
            js["server"]["port"].get<int>(),
            js["server"]["db_connection"].get<std::string>()
        };

        file.close();
    }

};

struct ClientConfig {
    int port;
    std::string ip;

    static ClientConfig load(const std::string& filename) {
        if(!fs::exists(filename) ||  fs::path(filename).extension() != ".json") {
            throw std::runtime_error("not correct config file or it does not exist");
        }
        std::ifstream file(filename);
        nlohmann::json js;
        file >> js;

        return ClientConfig {
            js["client"]["port"].get<int>(),
            js["client"]["ip"].get<std::string>()
        };

        file.close();
    }

};