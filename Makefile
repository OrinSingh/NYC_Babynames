all: output

output: main.o babyname.o babycollection.o command.o
	g++ main.o babyname.o babycollection.o command.o -o output

main.o: main.cpp
	g++ -c main.cpp

babyname.o: babyname.cpp babyname.h
	g++ -c babyname.cpp

babycollection.o: babycollection.cpp babycollection.h
	g++ -c babycollection.cpp

command.o: command.cpp command.h
	g++ -c command.cpp

clean:
	rm *.o output