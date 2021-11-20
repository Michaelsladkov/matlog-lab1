build: parsing/parser.cpp parsing/printer.cpp preprocessing/preprocessor.cpp analysis/analyser.cpp main.cpp
	g++ $^ -o runme

run:
	./runme