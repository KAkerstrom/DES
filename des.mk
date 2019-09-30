OBJS	= main.o src/BSHelper.cpp.src/DES.o
SOURCE	= main.cpp src/BSHelper.cpp.src/DES.cpp
HEADER	= include/BSHelper.h include/DES.h
OUT	= DES_Kyle_Akerstrom
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

src/BSHelper.cpp.src/DES.o: src/BSHelper.cpp.src/DES.cpp
	$(CC) $(FLAGS) src/BSHelper.cpp.src/DES.cpp 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)