CC = gcc 
CFLAGS = -O3 -g
TARGET = sed_simplified
SOURCES = main.c text_o.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	./$(TARGET) input.txt -r "old" "new"
test1: $(TARGET)
	./$(TARGET) input.txt -d "delete this"
test2: $(TARGET)
	./$(TARGET) input.txt -i -I ">> Add to start"
test3: $(TARGET)
	./$(TARGET) input.txt -i -b "Add to end <<"

.PHONY: clean test test1 test2 test3
