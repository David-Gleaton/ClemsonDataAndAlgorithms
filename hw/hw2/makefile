make1:
	g++ -o prog1 prog1.cpp
	g++ -o bad1 bad1.cpp
time1:	
	time ./bad1 100000 > input1
	time ./prog1 < input1
make2:
	g++ -o prog2 prog2.cpp
	g++ -o bad2 bad2.cpp
time2:	
	time ./bad2 100000 > input2
	time ./prog2 < input2
make3:
	g++ -o prog3 prog3.cpp
	g++ -o bad3 bad3.cpp
time3:	
	time ./bad3 100000 > input3
	time ./prog3 < input3 > output3
rr:	
	g++ -o prog3 prog3.cpp
	g++ -o bad3 bad3.cpp
	time ./bad3 100000 > input3
	time ./prog3 < input3 > output3
all:
	g++ -o prog1 prog1.cpp
	g++ -o bad1 bad1.cpp
	time ./bad1 100000 > input1
	time ./prog1 < input1
	g++ -o prog2 prog2.cpp
	g++ -o bad2 bad2.cpp
	time ./bad2 100000 > input2
	time ./prog2 < input2
	g++ -o prog3 prog3.cpp
	g++ -o bad3 bad3.cpp
	time ./bad3 100000 > input3
	time ./prog3 < input3 > output3



