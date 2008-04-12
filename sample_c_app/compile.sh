gcc -Wall -L /usr/local/lib -I /usr/local/include/webkit-1.0/ -g main.c -o main `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0 webkit-1.0`
