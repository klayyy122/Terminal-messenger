# About project
**A multi-user room-based chat system implemented in C++ using Boost.Asio for asynchronous networking. 

## Features
- **TLS/SSL Encryption** – Secure data transfer 
- **Room System** – Create, join, and manage persistent chat rooms.
- **Asynchronous Architecture** – Handles multiple concurrent connections using a non-blocking I/O model.
- **JSON Configuration** – Easy setup via `config.json` for both server and client.
- **Command Interface** – Control your session with intuitive commands (e.g., `/join_room`, `/help`).

## Requirements
- **C++17** or higher
- **Boost Libraries** (1.81.0+)
- **OpenSSL** 
- **nlohmann-json**
- **libpqxx** (for integration with PostgreSQL)
- **CMake** 3.20+

## Installation

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install g++ cmake libboost-all-dev libssl-dev libpqxx-dev nlohmann-json3-dev
```
### ArchLinux
```bash
sudo pacman -Syu
sudo pacman -S git gcc cmake boost boost-libs libpqxx nlohmann-json openssl
```

## Build & Run
```bash
git clone https://github.com/klayyy122/Terminal-messenger.git
cd Terminal-messenger

# Generation of a self-signed certificate and private key in one command:
openssl req -x509 -newkey rsa:2048 -keyout server.key -out server.crt -days 365 -nodes

mkdir build && cd build
cmake ..
make
```

## Usage

### Server starting

```bash
# Configure server/db settings in config.json first
./server
```

### Client starting

```bash
./client
```
## Session example

```bash
# Client 1
Enter login: alice
Create password: ******
> /create_room main
Room 'main' created
Joined room: main
> Hello!

# Client 2
Enter login: bob
Enter password: ******
> /join_room main
Joined room: main
[main] [alice]: Hello!
> Hi alice!
```

