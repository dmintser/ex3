all: compile link

#compile:
#	g++ -c HealthPoints.cpp HealthPoints.h HealthPointsExampleTest.cpp TestMain.cpp

#link:
#	g++ -o HealthPoints HealthPoints.o HealthPointsExampleTest.o TestMain.o

#clean:
#	rm -f HealthPoints *.o




compile:
	g++ -c -g3 Queue.h QueueExampleTests.cpp TestMain.cpp 

link:
	g++ -o Queue QueueExampleTests.o TestMain.o

clean:
	rm -f Queue *.o 
