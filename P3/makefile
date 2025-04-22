CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3

TARGET = partition
SRCS = main.cpp repeated.cpp karmakar.cpp experiments.cpp hill.cpp annealing.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
