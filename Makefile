SRC_DIR:= ./src
INC_DIR:= ./inc

CC:= g++
CPPFLAGS:= -g -pthread -Wall -rdynamic -I$(INC_DIR)
TARGET:= ./server.exe

SRCS:= $(wildcard ${SRC_DIR}/*.cpp)
OBJS:= $(SRCS:.cpp=.o)


$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CCFLAGS) -o $(TARGET)
	$(TARGET)


%.o: %.cpp %.hpp
	$(CC) -c $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	rm src/*.o