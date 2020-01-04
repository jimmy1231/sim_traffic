CXX = g++
CXXFLAGS = -Wall -g

OBJECTS1 = sim.o
EXEC1 = sim

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
	rm -f *.d *.o sim