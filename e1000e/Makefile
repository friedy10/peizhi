# Makefile for out-of-tree e1000e build

obj-m += e1000e.o

e1000e-y := 82571.o ich8lan.o 80003es2lan.o \
	    mac.o manage.o nvm.o phy.o \
	    param.o ethtool.o netdev.o ptp.o

ccflags-y += -I$(src)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
