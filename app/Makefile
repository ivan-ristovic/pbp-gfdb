CC      = gcc
CCFLAGS = -Wall -Wextra
PROGRAM = ../program
OBJ     =             \
    main.o            \
    helpers.o         \
    command_handler.o
VPATH    = src


%.o: %.c
	$(CC) -c -o $@ $< $(CCFLAGS)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CCLIBS) $(CCFLAGS)


.PHONY: clean

clean:
	rm -f src/*.swp *.swp *~ src/*~ *.o
