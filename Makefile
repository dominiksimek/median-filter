# Makefile

CXX=g++
CXXFLAGS=-std=c++11 -O3 -g -Wall -I. -I/usr/local/include
LDFLAGS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
BIN=med
OBJS=med.o sort.o utils.o merge.o
#OBJS=med.o utils.o

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BIN) $(LDFLAGS)

med.o: med.cc sort.h merge.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

sort.o: sort.cc sort.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

merge.o: merge.cc merge.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

utils.o: utils.cc utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

run:
	@./$(BIN)

clean:
	rm -f $(BIN) *.o
