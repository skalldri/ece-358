CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11 -O3
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp simulator.cpp packet_generator.cpp packet_server.cpp packet.cpp debug_log.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: net_sim

net_sim: $(OBJS)
	$(CXX) $(LDFLAGS) -o net_sim $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
