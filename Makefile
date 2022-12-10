


PROG=dinogame

CXX=g++-12
CXXFLAGS=-std=c++20 -Wall -Wextra -lncurses -D_DEBUG

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all : $(PROG)

$(PROG) : $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o : %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)


.PHONY: clean

clean:
	rm -f *.o *.gch $(PROG)
