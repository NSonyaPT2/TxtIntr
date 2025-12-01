CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
TARGET = calculator
SRC = calculator.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

test: $(TARGET)
	@echo "=== Тест 1: Умножение 3 чисел ==="
	./$(TARGET) -o multiply 2 3 4
	@echo ""
	@echo "=== Тест 2: Деление 4 чисел ==="
	./$(TARGET) --operation divide 100 2 5 2

.PHONY: all clean test