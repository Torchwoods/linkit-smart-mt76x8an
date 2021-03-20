#build a Makefile for helloOpenWrt.c
all:helloOpenWrt

helloOpenWrt: helloOpenWrt.o
	$(CC) $(LDFLAGS) helloOpenWrt.o -o helloOpenWrt
helloOpenWrt.o: helloOpenWrt.c
	$(CC) $(CFLAGS) -c helloOpenWrt.c
clean:
	rm *.o helloOpenWrt

