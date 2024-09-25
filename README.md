# Castle: secure banking transaction
built using C++

Set up Complier following this doc: [doc](https://code.visualstudio.com/docs/languages/cpp)


compile using: `g++ -I include -I"C:/Program Files/OpenSSL-Win64/include" -L"C:/Program Files/OpenSSL-Win64/lib" -o bin/main src/main.cpp src/Account.cpp src/Transaction.cpp src/Database.cpp src/Security.cpp src/AuditLog.cpp -lssl -lcrypto`

run using: `bin\main`

formatting shift + alt + f

manually download OpenSSL library on windows [link](https://slproweb.com/products/Win32OpenSSL.html)