CXX = g++
CXXFLAGS = -g

TARGET = main

SRC = user.cpp crypt.cpp login.cpp workspace.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp crypt.h workspace.h login.h splay.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET) info.txt

.PHONY: all clean run
