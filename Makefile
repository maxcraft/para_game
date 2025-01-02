.PHONY: all clean raylibpp

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
BIN := game_test
RAYLIB_HOME := $(shell realpath ~/opt)
RAYLIB_INCLUDE := $(RAYLIB_HOME)/include
RAYLIB_LIB:= $(RAYLIB_HOME)/lib
override CPPFLAGS += -I$(RAYLIB_INCLUDE)
override LDFLAGS += -L$(RAYLIB_LIB) -Lraylibpp

all: raylibpp $(BIN)

raylibpp:
	make -C $@

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ -lraylibpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	$(RM) $(BIN) $(OBJ) $(OBJ:.o=.d)
	make -C raylibpp clean

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(SRC:.cpp=.d)
