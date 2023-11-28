.PHONY: build run test

build:clean-build
	mkdir build
	cd ./build; gcc -pthread ../src/main.c ../src/include.c -lrt -o main;	gcc -pthread ../src/child1.c ../src/include.c -lrt -o child1; gcc -pthread ../src/child2.c ../src/include.c -lrt -o child2

run:
	cd build; ./main

clean-build:
	rm -rf ./build/

	