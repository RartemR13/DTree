comp:
	g++ DTree.cpp -c -o DTree.o
	g++ test.cpp -o test DTree.o

clean:
	rm test || true
	rm DTree.o || true