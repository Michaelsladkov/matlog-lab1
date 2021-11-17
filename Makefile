build: parsing/parser.cpp preprocessing/preprocessor.cpp checkers.cpp main.cpp
	g++ $^ -o runme

run: build
	./runme