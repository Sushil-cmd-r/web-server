SRC_DIR:= ./src
INC_DIR:= ./inc

CC:= g++
CPPFLAGS:= -g -pthread -Wall -rdynamic -I$(INC_DIR)
TARGET:= ./server.exe

SRCS:= $(wildcard ${SRC_DIR}/*.cpp)
OBJS:= $(SRCS:.cpp=.o)


$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CPPFLAGS) -o $(TARGET)


%.o: %.cpp %.h
	$(CC) -c $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm src/*.o
	rm $(TARGET)