# UDP Socket Communication in C

This project demonstrates how to implement UDP-based client-server communication using the C programming language. It includes basic socket setup, message exchange, asynchronous I/O using `select()`, and a stress test simulating 10,000 clients.

---

## 📌 Features

- ✅ Basic UDP client and server using `sendto()` and `recvfrom()`
- ✅ Asynchronous, non-blocking server using `select()`
- ✅ Performance/stress testing with 10,000 simulated UDP messages
- ✅ Prints client IP and port on each request
- ✅ Designed to run in a local development environment (127.0.0.1)

---

## 📁 Project Structure

```
udp-communication/
├── src/
│   ├── UDPClient.c               # Simple client that sends and receives a message
│   └── UDPServer.c               # Simple server that replies to each client
│
├── advanced/
│   └── ServerMultipleClient.c    # Non-blocking server using select()
│
├── tests/
│   └── 10kClient.c               # Simulates 10,000 clients sending messages
│
└── README.md
```

---

## 🚀 Getting Started

### 🔧 Requirements

- GCC (or any C compiler)
- Unix-like environment (Linux, WSL, macOS)

### 🛠 Compile

```bash
gcc src/UDPServer.c -o server
gcc src/UDPClient.c -o client
gcc advanced/ServerMultipleClient.c -o server_select
gcc tests/10kClient.c -o stress_test
```

### ▶️ Run

In separate terminals or processes:

```bash
./server           # Basic server
./client           # Basic client

# OR

./server_select    # Non-blocking select() based server
./stress_test      # Sends 10,000 UDP messages
```

---

## 🧠 What I Learned

- How to use low-level socket APIs in C: `socket()`, `bind()`, `sendto()`, `recvfrom()`
- Difference between TCP and UDP (connectionless, unordered, fast)
- Using `select()` and `fcntl()` to implement non-blocking I/O
- How to simulate massive numbers of clients for load testing
- IP/port parsing and diagnostic logging

---

## 🧪 Sample Output

```bash
Server with select() running on port 8080...
Received from 127.0.0.1:48730 → Client No 1
Received from 127.0.0.1:48731 → Client No 2
...
```

---

## 🧼 Extras (Optional)

Add the following to your `.gitignore` to keep your repo clean:

```
.vscode/
*.out
*.o
```

---

## 📬 Contact

Developed as part of my summer internship at **Movita**  
📧 [aenesozturk@gmail.com](mailto:aenesozturk@gmail.com)  
🌐 [https://github.com/aenesozturk](https://github.com/aenesozturk)

---

## 📝 License

This project is open source and free to use under the MIT License.
