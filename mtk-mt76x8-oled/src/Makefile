#if compile x86 demo on unbuntu 64.
CC:=mipsel-openwrt-linux-gcc
export STAGING_DIR:=/Users/mango/openwrt/openwrt-3.10.14/staging_dir

SRCS=$(wildcard *.c)
OBJS:=$(SRCS:%.c=%.o)

all: oled
	@echo build complete

clean:
	@rm oled $(OBJS)


oled:$(OBJS)
	$(CC) $(OBJS) -o $@ -O0 -g3 -I./


$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
