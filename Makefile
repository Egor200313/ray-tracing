build:
	g++ -o main --std=c++17 -lsfml-graphics -lsfml-window -lsfml-system main.cpp 

.PHONY: build
