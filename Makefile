all:
	g++ -std=c++17 ExceptionHW.h -o ExceptionHW
	g++ -std=c++17 ExceptionHW.cpp -o ExceptionHW
	g++ -std=c++17 ExceptionHWTest.cpp -o ExceptionHWTest

test:
	chmod +x ExceptionHW
	./ExceptionHWTest

clean:
	$(RM) ExceptionHW ExceptionHWTest