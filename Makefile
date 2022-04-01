test:
	g++ stress/stress_test.cpp -o stress/stress_test
	bash stress/stress.bash
clean:
	rm stress/stress_test || true
	rm out || true