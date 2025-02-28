CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

SRC = tree.cpp homographic.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = homographic

all: $(TARGET)

$(TARGET): homographic.o tree.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) homographic.o tree.o

tree.o: tree.cpp tree.h
	$(CXX) $(CXXFLAGS) -c tree.cpp

homographic.o: homographic.cpp tree.h
	$(CXX) $(CXXFLAGS) -c homographic.cpp

clean:
	rm -f $(OBJ) $(TARGET)
