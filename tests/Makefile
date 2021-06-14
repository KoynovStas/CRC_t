CXXFLAGS += -O2  -s  -Wall
CXXFLAGS += -D__USE_MINGW_ANSI_STDIO=1
CXXFLAGS += -I..
CXX      ?=  g++




# list of tests for build
TESTS  = crc_test


SPEED_TESTS = crc_test_speed


UNAME := $(shell uname)

ifneq ($(UNAME), Linux)
    BIN_TESTS       = $(addsuffix .exe, $(TESTS))
    BIN_SPEED_TESTS = $(addsuffix .exe, $(SPEED_TESTS))
else
    BIN_TESTS       = $(TESTS)
    BIN_SPEED_TESTS = $(SPEED_TESTS)
endif




.PHONY: all
all: $(BIN_TESTS)
	@for test in $(BIN_TESTS) ; do  \
        ./$$test ; \
    done



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(BIN_TESTS) $(BIN_SPEED_TESTS)



$(BIN_TESTS) $(BIN_SPEED_TESTS): crc_list.h
	$(CXX)  $(basename $@).cpp -o $@  $(CXXFLAGS)
	@echo "  ---- Compiled $@ ----"




.PHONY: speed
speed: CXXFLAGS += -std=c++11 -pthread
speed: $(BIN_SPEED_TESTS)
	@for test in $(BIN_SPEED_TESTS) ; do  \
        ./$$test ; \
    done




.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean  - remove all binary files"
	@echo "   all    - build an all tests (with out speed test)"
	@echo "   speed  - build and run all speed tests"
	@echo "   help   - This help"
