MODULE_NAME = memdrv

obj-m	:= $(MODULE_NAME).o

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

CFLAGS := -W -Wall -pedantic -g

all: module debug store-prog retreive-prog

module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

debug: debug.c libmemdrv.c libmemdrv.h fs.h
	gcc $(CFLAGS) -o debug debug.c libmemdrv.c

store-prog: store.c libmemdrv.c libmemdrv.h fs.h
	gcc $(CFLAGS) -o store-prog store.c libmemdrv.c 

retrieve-prog: retrieve.c libmemdrv.c libmemdrv.h fs.h
	gcc $(CFLAGS) -o retrieve-prog retrieve.c libmemdrv.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f debug store-prog retrieve-prog
