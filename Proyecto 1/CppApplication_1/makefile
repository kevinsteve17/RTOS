#
#  USAGE:
#     make          ... to build the program
#

include make.def

EXES= Scheduler$(EXE) PiCalculator$(EXE) 

all: $(EXES)

pi_Calc$(EXE): Scheduler.$(OBJ)
	$(CLINKER) $(OPTFLAGS) -o pi_scheduler$(EXE) PiCalculator.$(OBJ) Scheduler$(EXE) $(LIBS)

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(CC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(CC) $(CFLAGS) -c $<
