build: parsing/parser.cpp parsing/printer.cpp preprocessing/preprocessor.cpp main.cpp
	g++ $^ -o runme

run: build
	./runme