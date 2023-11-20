.PHONY: build run test

build:clean-build
	mkdir build
	cd ./build; g++  -pthread ../src/parallel.cpp -o main
run:
	cd build; ./main

clean-build:
	rm -rf ./build/