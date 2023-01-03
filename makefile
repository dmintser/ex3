all: compile link

compile:
	g++ -c HealthPoints.cpp HealthPoints.h HealthPointsExampleTest.cpp TestMain.cpp Queue.h QueueExampleTests.cpp

link:
	g++ -o ex3 HealthPoints.o HealthPointsExampleTest.o TestMain.o QueueExampleTests.o

clean:
	rm -f ex3 *.o




#compile:
#	g++ -c -g3 Queue.h QueueExampleTests.cpp TestMain.cpp 

#link:
#	g++ -o Queue QueueExampleTests.o TestMain.o

#clean:
#	rm -f Queue *.o 
