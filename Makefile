CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: main.exe

main.exe: main.cpp DynamicArray.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.exe

run: main.exe
	./main.exe

clean:
	rm -f main.exe
