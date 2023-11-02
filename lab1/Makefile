.PHONY: build run test

build:clean-build
	mkdir build
	cd ./build; gcc ../src/main.c ../src/include.c -o main;	gcc ../src/child1.c ../src/include.c -o child1; gcc ../src/child2.c ../src/include.c -o child2

run:
	cd build; ./main

clean-build:
	rm -rf ./build/

	