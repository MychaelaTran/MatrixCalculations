# Makefile for compiling and running matrix operations

# Compiler settings
CC = gcc
CFLAGS = -Wall -std=c99
# -Wall enables all the compiler's warning messages.
# -std=c99 tells the compiler to use the ISO C standard adopted in 1999.

# all the source files used to compile
SRCS = math_matrix.c functions.c
# Object files (takes all .c files and replaces the .c extension with .o)
# required bc without them the entire program would need to be compiled in a single step every time a change is made to any source file
OBJS = $(SRCS:.c=.o)

# executable name
EXEC = math_matrix

#target: all (gets executed when run make)
#dependencies: $(EXEC ~ math_matrix) (all the object files)
all: $(EXEC)

# rule to generate the executable
#rule is defined by the $(EXEC): $(OBJS) line, which means that the executable depends on all of the object files listed in $(OBJS)
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)
#action: tells make to use the GCC compiler ($(CC)) with the specified flags ($(CFLAGS)) to compile 
#and link the object files ($(OBJS)) into the final executable ($(EXEC))

# To generate object files from C source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
#matches each .c file with its .o counterpart, compiling them individually


#clean target
clean:
#echo displays the message to the terminal
	@echo "Removing everything but source files, SLAY!"
	rm -f $(OBJS) $(EXEC)
#rm removes
#-f force remove without prompting
#removes all the object files and the executable

#run target to run program with arguments
run:
	./$(EXEC) matrix nrows_A ncols_A nrows_B ncols_B operation [print]

# Placeholder target for 'print', replace or remove as necessary
[print]:
	@echo "Print option is not implemented in this Makefile directly."

.PHONY: all clean run [print]
#.PHONY tells make that these targets do not correspond to files, and should be executed regardless of the state of the filesystem
