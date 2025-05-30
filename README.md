# Non-Blocking UDP Communication in C

This is a simple client-server communication model using UDP sockets in C.  
The sockets are set to non-blocking mode using `fcntl()`, allowing asynchronous data handling.

## 🧠 Features
- Asynchronous (non-blocking) socket handling
- Client sends a message to server
- Server responds back to client
- Written in standard C with no external dependencies

## 🛠️ Compilation

```bash
gcc UDPServer.c -o server
gcc UDPClient.c -o client
