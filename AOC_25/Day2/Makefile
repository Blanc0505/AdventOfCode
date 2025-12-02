CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET   = Day2main
SRC      = Day2main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe