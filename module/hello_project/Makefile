obj-m += chardev.o
BUILD = /lib/modules/3.10.12csi500/build

all:
	gcc run.c -o run
	make -C $(BUILD) M=$(PWD) modules
clean:
	make -C $(BUILD) M=$(PWD) clean
    
