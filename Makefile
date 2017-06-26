# g++ -g main.cpp -o easylink -I/usr/local/include -L/usr/local/lib -lusb-1.0
CPPFLAGS=-g -std=c++11
INCFLAGS=-I/usr/local/include
LIBFLAGS=-L/usr/local/lib -lusb-1.0
OUTFILE=easylink

all:
	g++ $(CPPFLAGS) main.cpp -o $(OUTFILE) $(INCFLAGS) $(LIBFLAGS)