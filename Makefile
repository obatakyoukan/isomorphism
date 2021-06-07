CXX = g++
CXXFLAGS =  -O3 -std=c++17 -Iinclude/ 
DEBUGFLAGS = -Wall -O3 -std=c++17 -Iinclude/ 
OBJDIR = obj
EXECDIR = bin

#.SUFFIXES: .cpp .o
#.PHONY: all build clean

#all: .cpp.o
#%.o : %.cpp
#.cpp.o:
#	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/$@ -c $<


clean:
	rm $(EXECDIR)/*
	rm $(OBJDIR)/*




