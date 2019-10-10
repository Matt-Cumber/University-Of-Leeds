# Makefile for Matthew Cumber Compiler Project

EXE := jack-compiler

CXXFLAGS := -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -MMD

# Create a DEBUGGING macro
# When defined as DEBUG will print messages to command line
DEBUGGING := -DDEFAULT
CXXFLAGS += $(DEBUGGING)

SRCS := $(wildcard src/*.cpp)

OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(OBJS) -o $(EXE) 

-include $(DEPS)

clean:
	rm -f $(EXE)
	rm -f $(DEPS) $(OBJS)