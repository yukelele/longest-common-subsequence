CXX=g++

CXXFLAGS = -std=c++11 -Wall

all: findLCS

findLCS: findLCS.o
	${CXX} $^ -o $@

clean: 
	/bin/rm -f findLCS test_cases/#* *.o *~