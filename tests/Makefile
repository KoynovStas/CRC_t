CXXFLAGS += -O2 -s -Wall
CXXFLAGS += -D__USE_MINGW_ANSI_STDIO=1
CXXFLAGS += -I..
CXX      ?=  g++




# list of tests for build
TESTS  = crc_test


SPEED_TESTS = crc_test_speed


ifeq ($(OS),Windows_NT)
    BIN_SUFFIX      = .exe
    BIN_TESTS       = $(addsuffix $(BIN_SUFFIX), $(TESTS))
    BIN_SPEED_TESTS = $(addsuffix $(BIN_SUFFIX), $(SPEED_TESTS))
else
    BIN_TESTS       = $(TESTS)
    BIN_SPEED_TESTS = $(SPEED_TESTS)
endif




.PHONY: all
all: CXXFLAGS += -std=c++03
all: $(BIN_TESTS)
	@for test in $(BIN_TESTS) ; do  \
        ./$$test ; \
    done



.PHONY: speed
speed: CXXFLAGS += -std=c++11 -pthread
speed: $(BIN_SPEED_TESTS)
	@for test in $(BIN_SPEED_TESTS) ; do  \
        ./$$test ; \
    done



%$(BIN_SUFFIX): %.cpp crc_list.h ../crc_t.h
	$(CXX) $< -o $@  $(CXXFLAGS)
	@echo "  ---- Compiled $@ ----"



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(BIN_TESTS) $(BIN_SPEED_TESTS)



.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   all    - build an all tests (with out speed test)"
	@echo "   speed  - build and run all speed tests"
	@echo "   clean  - remove all binary files"
	@echo "   help   - This help"
