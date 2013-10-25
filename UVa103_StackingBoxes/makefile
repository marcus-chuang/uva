
FILENAME = StackingBoxes

CC = gcc
CFLAG = -lm -lcrypt -O2 -pipe -ansi

$(FILENAME): $(FILENAME).c makefile
	$(CC) $(CFLAG) $< -o $@
run:
	./$(FILENAME) < $(FILENAME).in > $(FILENAME).out 
	cat $(FILENAME).out
clean: 
	rm $(FILENAME)

.PHONY:clean run
