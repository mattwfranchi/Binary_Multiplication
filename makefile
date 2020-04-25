# Matt Franchi // Spring 2020 // CPSC 2310
# Lab Time : 330 PM

# Config, just variables
# CC - which compiler to use
CC=gcc
# CFLAGS - arguments for the compiler
CFLAGS=-Wall -g
# LFLAGS - flags to use during loading (i.e. -lm: links cmath library)
LFLAGS=-lm
# TARGET - name of the executable
TARGET=PA2

# Generate source and object lists, also just string variables
# C_SRCS - list of all the .c files in the directory range
C_SRCS := \
	# \ wraps the command onto next line, wildcard gets all files that
	# match the inputted conditions
	$(wildcard *.c) \
	$(wildcard src/*.c) \
	$(wildcard/**/*.c)

# HDRS - list of all the .h files in the directory range
HDRS := \
	$(wildcard *.h) \
	$(wildcard src/*.h) \
	$(wildcard src/**/*.h)

# OBJS - list of all .o files in directory range
#	 created by replacing filenames with suffix .c with .o
# patsubst - pattern substitute - replaces filenames with suffix *.c
#	     with bin/[filename].o
OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
# exclude existing .o files, make list of .o files from .c files in src directory
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))

#default target, always runs last
all: build
	@echo "All Done!"

#Link all built objects
# linking stage, runs after .o generation
build: $(OBJS)
	# $(__) causes string replacement
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

#which target
which:
	@echo "FOUND SOURCES: ${C_SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"

#special build rule
#catch root directory src files
#mkdir line creates the bin directory if it doesnt exist
bin/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#catch all nested directory files
bin/%.o: src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#clean rule
# delete the executable file, and all files in the bin directory
clean:
	rm -f $(TARGET)
	rm -rf bin

#build rule
# run the executable file
run: build
	./$(TARGET)
