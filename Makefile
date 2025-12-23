CC=gcc
PHONY= all clean configure half_configure

all:
	$(CC) src/main.c -o build/ez-login-manager
	cp src/users.txt build/users.txt
	cp src/password.txt build/password.txt

clean:
	rm -rf build/

half_configure:
	mkdir build/

configure:
	mkdir build/
	touch src/users.txt
	touch src/password.txt
