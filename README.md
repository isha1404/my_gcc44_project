# Simple Messaging Service

A simple command-line messaging service implemented in C++ and compatible with GCC 4.4.

## Features

- User registration and authentication
- Sending and receiving messages
- Viewing message history
- Command-line interface

## Building the Project

This project is designed to be compatible with GCC 4.4. To build the project:

```bash
make
```

## Running the Application

After building, run the application with:

```bash
./messaging_service
```

## Available Commands

- `register <username>` - Register a new user
- `login <username>` - Login as a user
- `logout <username>` - Logout a user
- `send <username> <message>` - Send a message as a user
- `messages` - Display all messages
- `users` - Display all registered users
- `help` - Display help message
- `exit` - Exit the program

## Implementation Details

The project consists of the following components:

- `Message` class - Represents a message with sender, content, and timestamp
- `User` class - Represents a user with username and online status
- `ChatService` class - Manages users and messages
- Command-line interface in `main.cpp`
