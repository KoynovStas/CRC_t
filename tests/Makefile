CPPFLAGS += -O2  -s  -Wall
CPPFLAGS += -D__USE_MINGW_ANSI_STDIO=1  #-DWITHOUT_COLOR_COLOR
CPPFLAGS += -I..
CPP       =  g++
#CPP       =  arm-gcc_4.9.2_cortex_a15-linux-uclibcgnueabi-g++



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
	$(CPP)  $@.cpp -o $@  $(CPPFLAGS)
	@echo "  ---- Compiled $@ ----"
	@./crc_test



.PHONY: asm
asm:
	$(CPP)  crc_test.cpp $(CPPFLAGS) -S




.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean   -  remove all binary files"
	@echo "   all     -  clean and build all tests"
	@echo "   asm     -  get ASM listing"
	@echo "   help    -  This help"

