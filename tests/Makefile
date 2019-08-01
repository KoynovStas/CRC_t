CXXFLAGS += -O2  -s  -Wall
CXXFLAGS += -D__USE_MINGW_ANSI_STDIO=1  #-DWITHOUT_CONSOLE_COLOR
CXXFLAGS += -I..
CXX      ?=  g++
#CXX      ?=  arm-gcc_4.9.2_cortex_a15-linux-uclibcgnueabi-g++




# list of tests for build
TESTS  = crc_test


SPEED_TESTS = crc_test_speed


ALL_TESTS = $(TESTS) $(SPEED_TESTS)



UNAME := $(shell uname)

ifneq ($(UNAME), Linux)
ALL_TESTS = $(addsuffix .exe, $(ALL_TESTS))
endif




.PHONY: all
all: $(TESTS)
	@for test in $(TESTS) ; do  \
        ./$$test ; \
    done



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(ALL_TESTS)



$(ALL_TESTS): crc_list.h
	$(CXX)  $(basename $@).cpp -o $@  $(CXXFLAGS)
	@echo "  ---- Compiled $@ ----"




.PHONY: speed
speed: CXXFLAGS += -std=c++11 -lpthread
speed: $(SPEED_TESTS)
	@for test in $(SPEED_TESTS) ; do  \
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
