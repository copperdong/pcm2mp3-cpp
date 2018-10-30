LIBDEPS := -lmp3lame -ltag
LIBNAME := libpcm2mp3
EXENAME := transcode

LIBDIR := ../../lib/${LIBNAME}
BINDIR := ../../bin
INCDIR := ../../include/${LIBNAME}






CXX := g++
AR := ar
RANLIB := ranlib
CXXFLAGS := -std=c++14 -pthread -O3 -g3 -Wall -c -fmessage-length=0 -fPIC
LKRFLAGS := $(LIBDEPS)


LIB := $(addprefix $(LIBDIR)/,$(LIBNAME).so $(LIBNAME).a)
EXE := $(EXENAME)

OBJ := $(patsubst %.cpp,%.o,$(filter %.cpp, $(shell find . -name '*.cpp')))
LIB_OBJ := $(filter-out %$(EXE).o, $(OBJ))




MKDIR := mkdir -p
RM := rm -fr
CP := cp



.PHONY: all
all: prepare $(LIB) $(EXE)

.PHONY: lib
lib : prepare $(LIB)

.PHONY: app
app : prepare $(EXE)

.PHONY: prepare
prepare:
	$(MKDIR) $(BINDIR)
	$(MKDIR) $(INCDIR)
	$(MKDIR) $(LIBDIR)
	$(CP) *.hpp $(INCDIR)


clean:
	$(RM) *.o
	$(RM) $(INCDIR)/*.hpp

.PHONY: distclean
distclean: clean
	$(RM) $(INCDIR)
	$(RM) $(LIBDIR)
	$(RM) $(BINDIR)/${EXENAME}
	
.PHONY: list
list: 
	$(info Source dir is .)
	$(info File list is $(OBJ))
	$(info Library file list is $(LIB_OBJ))

$(EXE): $(OBJ)
	$(CXX) $(LKRFLAGS) $^ -o $(BINDIR)/$@ 
	
$(LIB): $(LIB_OBJ)
	$(AR) cr $@ $^
	$(RANLIB) $@
	
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $@ $<
