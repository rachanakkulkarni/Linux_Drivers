obj-m += kmalloc.o

all: kmalloc.ko t

kmalloc.ko: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

t: test.c
	gcc $< -o $@

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	$(RM) t
