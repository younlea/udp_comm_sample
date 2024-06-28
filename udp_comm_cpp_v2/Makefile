CXX = g++
CXXFLAGS = -std=c++11 -I./include

SRCS = src/main.cpp src/UdpComm.cpp src/CustomUdpComm.cpp src/another_file.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = udp_comm_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
