EXEC = m

SRC = $(wildcard *.cpp ../../console/*.cpp ../../app/*.cpp ../../loaders/*.cpp ../../gl/*.cpp)
OBJ = $(SRC:.cpp=.o)

CXX = g++-4.5

#WARNINGSFLAGS = -W -Werror -Wall -Wfatal-errors -pedantic -pedantic-errors

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(EXEC) $(OBJ) -lplastic-core -lplastic-gui -lplastic-ressource -lplastic-graphics -lGL

%.o: %.cpp
	$(CXX) -o $@ -c $< $(WARNINGSFLAGS) -std=c++0x -O3

.PHONY: clean mrproper

clean:
	rm -rf $(OBJ)

mrproper: clean
	rm -rf ./$(EXEC)
