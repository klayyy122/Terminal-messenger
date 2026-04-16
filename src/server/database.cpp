#include"database.hpp"

void Database::create_tables() {
    pqxx::work W(*conn_);

    W.exec(R"(
        CREATE TABLE IF NOT EXISTS users (
        id SERIAL PRIMARY KEY,
        username TEXT,
        password TEXT NOT NULL
        );
    )");
    W.commit();
}

void Database::prepare_statements() {
    conn_->prepare("find_user", "SELECT password FROM users WHERE username = $1");
    conn_->prepare("add_user", "INSERT INTO users (username, password) VALUES($1, $2)");
}

bool Database::register_user(const std::string& login, const std::string& password) {
    try {
        pqxx::work W(*conn_);
        W.exec_prepared("add_user", login, password);
        W.commit();
        return true;
    } catch (const std::string& e){
        return false;
    }
}

std::string Database::get_password(const std::string& login){
    pqxx::nontransaction N(*conn_);
    pqxx::result R = N.exec_prepared("find_user", login);
    if(R.empty()) return "";
    return R[0][0].as<std::string>();
}