CXX = g++
CXXFLAGS = -Wall -std=c++20 -I/opt/homebrew/Cellar/raylib/5.5/include
LDFLAGS = -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib -lm -ldl -lpthread

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: main

main: $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o main $(LDFLAGS)

clean:
	rm -f main $(OBJS)
