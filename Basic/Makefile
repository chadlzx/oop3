# You may modify Makefile as your like
# but you should keep `make clean` and `make` works correct
SHELL = powershell.exe
PROGRAM = Basic

CXX = g++
CXXFLAGS = -IStanfordCPPLib -fvisibility-inlines-hidden -g -std=c++14

CPP_FILES = $(wildcard *.cpp)
H_FILES = $(wildcard *.h)

LDOPTIONS = -L.
LIB = -lStanfordCPPLib

all:clean $(PROGRAM) spl.jar score

$(PROGRAM): $(CPP_FILES) $(H_FILES) libStanfordCPPLib.a
	$(CXX) -o $(PROGRAM).exe $(CXXFLAGS) $(LDOPTIONS) $(CPP_FILES) $(LIB)

score: ../Test/score
	cmd /c "mklink /H score.exe ..\Test\score.exe"

../Test/score:
	powershell /c "cd ../Test; make"

libStanfordCPPLib.a:
	@if (Test-Path ../libStanfordCPPLib.a) {rd -Force ../libStanfordCPPLib.a}
	powershell /c "cd ../StanfordCPPLib; make all"
	cmd /c "mklink /H libStanfordCPPLib.a ..\StanfordCPPLib\libStanfordCPPLib.a"

spl.jar:
	cmd /c "mklink /H spl.jar ..\StanfordCPPLib\spl.jar"

tidy:
	rd -Force *~
	if (Test-Path core) {rd -Force core}
	if (Test-Path a.out) {rd -Force a.out}
	rd -Force *.err

clean scratch: tidy
	rd -Force *.o
	rd -Force *.a
	if (Test-Path $(PROGRAM).exe) {rd -Force $(PROGRAM).exe}
	if (Test-Path spl.jar) {rd -Force spl.jar}
	if (Test-Path score.exe) {rd -Force score.exe}
