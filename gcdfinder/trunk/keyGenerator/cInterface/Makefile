CC=g++
CFLAGS=-g -O3 -Wall
LFLAGS=-lpthread -ldl
ALL=getKeysTest getKeys.o sqlite3.o cfmemopen.o

all: $(ALL)

getKeysTest: getKeysTest.cpp getKeys.o sqlite3.o libcrypto.a libssl.a cfmemopen.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS) 

getKeys.o: getKeys.cpp sqlite3.o libcrypto.a libssl.a cfmemopen.o
	$(CC) $(CFLAGS) -o $@ -c $^ $(LFLAGS) 

sqlite3.o: sqlite3.c
	gcc $(CFLAGS) -o $@ -c $^ $(LFLAGS) 

cfmemopen.o: cfmemopen.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(LFLAGS) 

clean:
	rm -rf core* *.o *.gch $(ALL)
