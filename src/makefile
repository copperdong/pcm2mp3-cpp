RM := rm -fr

CXX := g++
CXXFLAGS := -std=c++14 -pthread -O3 -g3 -Wall -c -fmessage-length=0 -fPIC
LKRFLAGS :=

BINDIR := ../bin
EXE := mp3header
OBJ := mp3header.o info/MP3.o info/MP3Frame.o

$(EXE) : $(OBJ)
	$(CXX) $(LKRFLAGS) $^ -o $(BINDIR)/$@

clean:
	$(RM) *.o	
	
.PHONY: distclean
distclean: clean
	$(RM) $(BINDIR)/$(EXE)
	
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $@ $<

	
	
	