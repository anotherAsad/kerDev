obj-m += code.o
all:
	make -C /lib/modules/5.8.0-43-generic/build M=$(PWD) modules
std:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
