Preferred on a Unix/Linux Environment. So for Windows, kindly use WSL.

Debian:
```
sudo apt install build-essential libmysqlcppconn-dev
```

or any g++ compiler of your choosing.

compile command:

```
g++ -o main -Iinclude -Llib -L/usr/bin/mysql main.cpp -lmysqlcppconn
```

run command:
```
./main
```

There's lots codes that can be optimized like just doing 1 connection for all. Simplying the codes and etc. So feel free to use this as your assignment answer but please. Do change the code to make it better when you submit your assignment, No need to do a Pull Request as this project is to help Uni students get a glimpse of their assignment and make it better. Learn as I did using [Agusk's work] and [CWC's Music Store].

Disclaimer: this project was made using both [Agusk's work] and [CWC's Music Store] by merging the two, I manage to help develop this system for a friend.

[Agusk's work]: https://github.com/agusk/crud-mysql-cpp
[CWC's Music Store]: https://www.codewithc.com/music-store-management-system-c-program-with-mysql-database/

