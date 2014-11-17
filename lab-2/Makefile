CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-s -std=c++11 -O3 -march=native -Ofast
LDFLAGS=-s
LDLIBS=

SRCS=main.cpp simulator.cpp computer.cpp network_medium.cpp packet.cpp debug_log.cpp
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
