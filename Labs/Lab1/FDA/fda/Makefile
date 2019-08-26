OBJ = basis.o del2.o densityx.o fda.o hamilx.o jandx.o nl.o oper1.o orbital.o overlap.o rm1.o rm2.o rp1.o vector.o

# compiler/loader/options
CXX = g++
LD = g++
CFLAGS = -c -O
LIBS = -lm
#
# use -DEBUGGED if all the array indexing and basis compatibility
#     problems have been cleaned up
# use -DHAVE_LOG1P if libm.a has log1p
#
DEFINES = -DEBUGGED -DHAVE_LOG1P

.SUFFIXES: .cxx .C .o

.cxx.o:
	$(CXX) $(CFLAGS) $(DEFINES) $<

.C.o:
	$(CXX) $(CFLAGS) $(DEFINES) $<

fda:	$(OBJ)
	$(LD) -o $@ $(OBJ) $(LIBS)

clean:
	rm -f $(OBJ)
