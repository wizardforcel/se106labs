CPP_FILES = $(wildcard *.cpp)
H_FILES = $(wildcard *.h)
PROGRAM = Compression

Compression: $(CPP_FILES) $(H_FILES)
	g++ -o $(PROGRAM) $(CPP_FILES) -Wall -O2 -std=c++11
debug: $(CPP_FILES) $(H_FILES)
	g++ -o $(PROGRAM) $(CPP_FILES) -Wall -O2 -std=c++11 -D_DEBUG
clean:
	rm -f *.o *.tmp *~ $(PROGRAM)
cleanlog:
	rm -f *.log
