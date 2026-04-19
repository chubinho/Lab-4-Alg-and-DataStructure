CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = lab4
TEST_TARGET = rbt_tests
SRCS = main.c RB_tree.c RBdelete_node.c 
OBJS = $(SRCS:.c=.o)

TEST_SRCS = test_lab4.c RB_tree.c RBdelete_node.c
TEST_OBJS = test_lab4.o RB_tree.o RBdelete_node.o

all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

test: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)
	./$(TEST_TARGET)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


run:
	./$(TARGET)

clean:
	del /f /q *.o $(TARGET).exe $(TEST_TARGET).exe 2>nul || exit 0

.PHONY: all clean run test