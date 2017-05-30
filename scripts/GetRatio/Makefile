#-------------------------------------------
# Makefile for any C program with ROOT lib
# Zhihong Ye, 01/09/2009
#-------------------------------------------

PROGRAM = GetRatio
CXX:="$(shell $(ROOTSYS)/bin/root-config --cxx)"
CFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags)
LIBS   = $(shell $(ROOTSYS)/bin/root-config --libs)
GLIBS  = $(shell $(ROOTSYS)/bin/root-config --glibs)

CFLAGS += -Wall -g
INCLUDE := -I${ROOTSYS}/include
RTLIBS := -L${ROOTSYS}/lib -lCore
all: $(PROGRAM)

$(PROGRAM): $(PROGRAM).o
	$(CXX) -o $(PROGRAM) $(PROGRAM).o $(CFLAGS) $(LIBS) $(RTLIBS)

$(PROGRAM).o: $(PROGRAM).C
	$(CXX) $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).C ${INCLUDE}

clean:
	rm -f *.o	
