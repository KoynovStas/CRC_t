CXXFLAGS += -O2  -s  -Wall
CXXFLAGS += -D__USE_MINGW_ANSI_STDIO=1  #-DWITHOUT_CONSOLE_COLOR
CXXFLAGS += -I..
CXX      ?=  g++
#CXX      ?=  arm-gcc_4.9.2_cortex_a15-linux-uclibcgnueabi-g++



# list of tests for build
TESTS  = crc_test




.PHONY: all
all: clean  $(TESTS)



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(TESTS)



.PHONY: $(TESTS)
$(TESTS):
	$(CXX)  $@.cpp -o $@  $(CXXFLAGS)
	@echo "  ---- Compiled $@ ----"
	@./$@



.PHONY: asm
asm:
	$(CXX)  crc_test.cpp $(CXXFLAGS) -S




.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean   -  remove all binary files"
	@echo "   all     -  clean and build all tests"
	@echo "   asm     -  get ASM listing"
	@echo "   help    -  This help"
