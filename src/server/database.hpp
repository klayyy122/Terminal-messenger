#pragma once
#include<iostream>
#include<pqxx/pqxx>
#include<memory>
#include<string>


class Database {
    std::unique_ptr<pqxx::connection> conn_;
    void create_tables();
    void prepare_statements();
public:
    Database(const std::string& db_name){
        conn_ = std::make_unique<pqxx::connection>(db_name);

        if(conn_->is_open()){
            std::cout << "Connected to db: " << conn_->dbname() << std::endl;
            this->create_tables();
            this->prepare_statements();
        }
    }
    bool register_user(const std::string& login, const std::string& password);
    std::string get_password(const std::string& login);
};