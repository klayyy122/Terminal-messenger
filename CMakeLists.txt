cmake_minimum_required(VERSION 3.20)
project(TerminalMessenger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


cmake_policy(SET CMP0167 NEW)

find_package(PkgConfig REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost 1.89 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)


add_executable(server 
    src/server/server.cpp 
    src/server/room.cpp 
    src/server/chat_session.cpp 
    src/server/database.cpp
)

add_executable(client 
    src/client/main_client.cpp 
    src/client/client.cpp
)

configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_CURRENT_BINARY_DIR}/config.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/server.crt ${CMAKE_CURRENT_BINARY_DIR}/server.crt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/server.key ${CMAKE_CURRENT_BINARY_DIR}/server.key COPYONLY)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


target_include_directories(server PRIVATE src/server)

target_link_libraries(server PRIVATE 
    PkgConfig::PQXX    
    Boost::headers     
    Threads::Threads
    OpenSSL::SSL
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
)


target_include_directories(client PRIVATE src/client src/server)

target_link_libraries(client PRIVATE 
    Boost::headers     
    Threads::Threads
    OpenSSL::SSL
    OpenSSL::Crypto
)