FILE = projecto
INPUT = $(FILE).cpp
OBJECTS = $(FILE).o
CXX = g++ 
CXXFLAGS = -O3 -ansi -Wall
LDFLAGS = -lm       # put linker settings here

all: $(FILE)

debug: CXX += -DDEBUG -g
debug: $(FILE)

$(FILE): $(OBJECTS)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $(OBJECTS)

.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

clean: 
	rm -f $(FILE) *.o *.out