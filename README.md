# About project
**A multi-user room-based chat system implemented in C++ using Boost.Asio for asynchronous networking. 

## ✨ Features
- Room system - creating, joining, and managing chat rooms

- Asynchronous server - handling multiple connections without blocking

- Group chat - real-time communication

- Thread safety - secure data structures

- Command interface - control via simple commands

## Requirements

- C++ 17
- Boost libs(1.66+)
- CMake 4.0+

## Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install g++ cmake libboost-all-dev
```
## ArchLinux
```bash
sudo pacman -Syu
sudo pacman -S git gcc cmake boost boost-libs
```

## Build
```bash
git clone https://github.com/username/Terminal-messenger.git
cd Terminal-messenger

mkdir build && cd build

cmake ..
make
```
## Usage

### Server starting
```bash
./server <port>
# Example:
./server 1111
```
# Client starting
```bash
./client

# Client connects by default 127.0.0.1:1111
```
## Session example

```bash
# Клиент 1
Enter login: alice
Create password: ******
> /create_room main
Room 'main' created
Joined room: main
> Hello!

# Клиент 2
Enter login: bob
Enter password: ******
> /join_room main
Joined room: main
[main] [alice]: Hello!
> Hi alice!
```

