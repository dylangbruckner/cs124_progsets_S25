CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3

TARGET = strassen
SRCS = main.cpp strassens.cpp triangle.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
