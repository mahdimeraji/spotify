

CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: sputify.out

sputify.out: main.o System_Interface.o Exceptions.o System.o User.o Artist.o Music.o PlayList.o
	$(CXX) $(CXXFLAGS) main.o System_Interface.o Exceptions.o System.o User.o Artist.o Music.o PlayList.o -o sputify.out  

main.o: main.cpp System_Interface.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

System_Interface.o: System_Interface.cpp System_Interface.hpp 
	$(CXX) $(CXXFLAGS) -c System_Interface.cpp

Exceptions.o:  Exceptions.cpp  Exceptions.hpp
	$(CXX) $(CXXFLAGS) -c Exceptions.cpp 

System.o: System.cpp System.hpp User.hpp Exceptions.hpp System_Interface.hpp Artist.hpp Music.hpp
	$(CXX) $(CXXFLAGS) -c System.cpp

User.o: User.cpp User.hpp Exceptions.hpp PlayList.hpp
	$(CXX) $(CXXFLAGS) -c User.cpp

Artist.o: Artist.cpp Artist.hpp Exceptions.hpp
	$(CXX) $(CXXFLAGS) -c Artist.cpp

Music.o: Music.cpp Music.hpp Exceptions.hpp Artist.hpp
	$(CXX) $(CXXFLAGS) -c Music.cpp

PlayList.o: PlayList.cpp PlayList.hpp Music.hpp
	$(CXX) $(CXXFLAGS) -c PlayList.cpp
	
clean:
	rm -f *.o sputify.out 
