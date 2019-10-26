CXX = g++
CXXFLAGS = -Wall -g

OBJECTS1 = main.o
EXEC1 = main

OBJECTS = $(OBJECTS1)
DEPENDS = $(OBJECTS:.o=.d)
EXECS = $(EXEC1)

####################################

.PHONY : all clean

all : $(EXECS)

$(EXEC1): $(OBJECTS1)
	$(CXX) $(CXXFLAGS) $< -o $@

####################################

#-include $(DEPENDS)

clean:
	rm -f *.d *.o main