.PHONY: all clean

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
BIN := libraylibpp.a

RAYLIB_HOME := $(shell realpath ~/opt)
RAYLIB_INCLUDE := $(RAYLIB_HOME)/include
RAYLIB_LIB:= $(RAYLIB_HOME)/lib
override CPPFLAGS += -I$(RAYLIB_INCLUDE)
override LDFLAGS += -L$(RAYLIB_LIB)
AR ?= ar

all: $(BIN)

$(BIN): $(OBJ)
	$(AR) rcs $@ $^

clean:
	$(RM) $(BIN) $(OBJ) $(OBJ:.o=.d)

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
