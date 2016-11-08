
CC = gcc
SOURCE = $(wildcard *.c)
OBJ = $(SOURCE:.c=)

TEST = $(join 111 222 333, aaa bbb ccc)


MAKE = make


.PHONY : all $(OBJ)


all: first folders

first : $(OBJ)
	@echo hello
	@echo "\$$@: $@"
	@echo "\$$<: $<"
	@echo "\$$?: $?"
	@if [ "gcc" = "gcc" ] ;then echo "hello gcc"; fi
	@echo "source: $(SOURCE)"
	@echo "obj: $(OBJ)"
	@echo "test: $(TEST)"

$(OBJ) : % : %.c
	@echo "hello compile"
	@echo "\$$@: $@"
	@echo "\$$<: $<"
	@echo "\$$?: $?"
	$(CC) -o program_$(basename $?) $?



SUB_DIRS = $(sort $(subst /,,$(dir $(wildcard */*))))


folders :: $(SUB_DIRS)
	@echo  $(wildcard */*)
	@echo $(sort $(subst /,,$(dir $(wildcard */*))))
	@for i in $(SUB_DIRS); do \
	    echo $$i;\
	    done
