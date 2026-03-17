CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = main

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)