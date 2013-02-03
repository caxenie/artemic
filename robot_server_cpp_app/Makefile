
CC=g++ 

RTAIDIR=/usr/realtime
COMEDIDIR=/usr/src/comedi
COMEDILIBDIR=/usr/src/comedilib


HRTAI    = $(RTAIDIR)
HCOMEDI  = $(COMEDIDIR)/include

COMEDIFLAGS := -I$(HCOMEDI) -lcomedi -L/usr/realtime/lib/libkcomedilxrt.a
RTAIFLAGS := -I$(HRTAI)/include


LINUXDIR:=/usr/src/linux

HLINUX:=$(LINUXDIR)/include

CPPFLAGS := -I$(HLINUX) -pthread -Wno-deprecated -O2 -Wall -Wstrict-prototypes -fomit-frame-pointer -fno-strength-reduce -pipe -Wno-missing-braces


all:
	$(CC) $(RTAIFLAGS) $(CPPFLAGS) $(COMEDIFLAGS) -o main main.cpp grafcet.cpp
