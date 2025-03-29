CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3

TARGET = trassen
SRCS = main.cpp strassens.cpp triangle.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
