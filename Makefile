# C compiler options
CC	= gcc
#CC	= x86_64-w64-mingw32-gcc
CFLAGS=         
RELEASE	= release.elf
DEBUG	= debug.elf
LIBS = 
INC	= 
LDFLAGS := -L /usr/local/lib
DEFINES :=
INCLUDE := -I ./include/
CFLAGS  := 
CXXFLAGS:= 


# Source files
SRCS = test_main.c
OBJS = librelic_s.a libgmp.a
TARGET = 


# Make everything
all:	$(RELEASE) 
debug: $(DEBUG)
# Make the application
$(RELEASE): $(OBJS)
	$(CC) -o $(RELEASE) $(SRCS) $(LIBS) $(CFLAGS) 

$(DEBUG): $(OBJS)
	$(CC) -g -ggdb3 -o $(DEBUG) $(SRCS)  $(LIBS) $(CFLAGS) 
	gdbserver :1234 $(DEBUG)

#
# Clean all object files...
#
clean:
	$(RM) $(DEBUG) $(RELEASE) 
