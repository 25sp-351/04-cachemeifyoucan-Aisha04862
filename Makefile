CC = gcc
CFLAGS = -Wall

all: rodcut_lru rodcut_lfu

rodcut_lru: rodcut.c cache_lru.c
	$(CC) -o rodcut_lru $(CFLAGS) rodcut.c cache_lru.c

rodcut_lfu: rodcut.c cache_lfu.c
	$(CC) -o rodcut_lfu $(CFLAGS) rodcut.c cache_lfu.c

clean:
	rm -f rodcut_lru rodcut_lfu *.o