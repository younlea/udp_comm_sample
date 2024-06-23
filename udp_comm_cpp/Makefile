CXX = g++
CXXFLAGS = -std=c++11 -pthread

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/udpcomm.cpp $(SRC_DIR)/customudpcomm.cpp
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/udpcomm.o $(OBJ_DIR)/customudpcomm.o

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o udp_program $(OBJS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/udpcomm.hpp $(INC_DIR)/customudpcomm.hpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/udpcomm.o: $(SRC_DIR)/udpcomm.cpp $(INC_DIR)/udpcomm.hpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/udpcomm.cpp -o $(OBJ_DIR)/udpcomm.o

$(OBJ_DIR)/customudpcomm.o: $(SRC_DIR)/customudpcomm.cpp $(INC_DIR)/customudpcomm.hpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/customudpcomm.cpp -o $(OBJ_DIR)/customudpcomm.o

clean:
	rm -f $(OBJ_DIR)/*.o udp_program
