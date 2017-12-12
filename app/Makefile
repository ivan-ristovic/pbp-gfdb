CC      = gcc
CCLIBS  = -I/usr/include/mysql/ -lmysqlclient
CCFLAGS = -Wall -Wextra
PROGRAM = ../program
OBJ     =             \
    main.o            \
    helpers.o         \
    command_handler.o
VPATH    = src


%.o: %.c
	$(CC) -c -o $@ $< $(CCLIBS) $(CCFLAGS)

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CCLIBS) $(CCFLAGS)


.PHONY: clean

clean:
	rm -f src/*.swp *.swp *~ src/*~ *.o
