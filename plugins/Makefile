CC=gcc
CFLAGS=-shared -fPIC -O2

%.so: %.c
	$(CC) $(CFLAGS) -o $@ $<
	
all: $(patsubst %.c,%.so,$(wildcard *.c))

# Uses the default install directory for now.
install: all
	install $(wildcard *.so) /usr/local/backupd/plugins