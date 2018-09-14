CC=g++
CPPFLAGS=-g -Wall
USERID=404561839

all: server client

server: $(CLASSES)
	$(CC) -o $@ $^ $(CPPFLAGS) $@.cpp

client: $(CLASSES)
	$(CC) -o $@ $^ $(CPPFLAGS) $@.cpp

clean:
	rm -rf *.o *~ *.gch *.swp *.dSYM server client *.tar.gz

dist: tarball

tarball: clean
	tar -cvzf /tmp/$(USERID).tar.gz --exclude=./.vagrant . && mv /tmp/$(USERID).tar.gz .
