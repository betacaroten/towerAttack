CXX = g++ -std=c++11 -g
CXXFLAGS = -Wall -pedantic
LFLAGS = -lncurses
OUTPUT_BIN = .
BIN = towerattack
SRC = src
OFILES = Screen.o Game.o Map.o Archer.o BasicTower.o ComputerPlayer.o \
HumanPlayer.o Player.o Pawn.o Entity.o Field.o IceTroll.o FireTower.o IceTower.o \
MountainTroll.o Parser.o Blank.o Wall.o Point.o Raider.o Tower.o Range.o \
ShockTower.o SniperTower.o TorchMan.o

all: compile doc

compile: $(OFILES)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT_BIN)/$(BIN) $(SRC)/main.cpp $(OFILES) $(LFLAGS)

main.o: $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp $(LFLAGS)

Screen.o: $(SRC)/Screen.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Screen.cpp $(LFLAGS)

Parser.o: $(SRC)/Parser.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Parser.cpp $(LFLAGS)

Game.o: $(SRC)/Game.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Game.cpp $(LFLAGS)

Point.o: $(SRC)/Point.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Point.cpp $(LFLAGS)

Range.o: $(SRC)/Range.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Range.cpp $(LFLAGS)

Field.o: $(SRC)/Field.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Field.cpp $(LFLAGS)

Entity.o: $(SRC)/Entity.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Entity.cpp $(LFLAGS)

Raider.o: $(SRC)/Raider.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Raider.cpp $(LFLAGS)

Tower.o: $(SRC)/Tower.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Tower.cpp $(LFLAGS)

Blank.o: $(SRC)/Blank.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Blank.cpp $(LFLAGS)

Wall.o: $(SRC)/Wall.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Wall.cpp $(LFLAGS)

Map.o: $(SRC)/Map.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Map.cpp $(LFLAGS)

Player.o: $(SRC)/Player.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Player.cpp $(LFLAGS)

ComputerPlayer.o: $(SRC)/ComputerPlayer.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/ComputerPlayer.cpp $(LFLAGS)

HumanPlayer.o: $(SRC)/HumanPlayer.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/HumanPlayer.cpp $(LFLAGS)

Archer.o: $(SRC)/Archer.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Archer.cpp $(LFLAGS)

Pawn.o: $(SRC)/Pawn.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/Pawn.cpp $(LFLAGS)

TorchMan.o: $(SRC)/TorchMan.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/TorchMan.cpp $(LFLAGS)

IceTroll.o: $(SRC)/IceTroll.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/IceTroll.cpp $(LFLAGS)

MountainTroll.o: $(SRC)/MountainTroll.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/MountainTroll.cpp $(LFLAGS)

BasicTower.o: $(SRC)/BasicTower.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/BasicTower.cpp $(LFLAGS)

IceTower.o: $(SRC)/IceTower.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/IceTower.cpp $(LFLAGS)

FireTower.o: $(SRC)/FireTower.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/FireTower.cpp $(LFLAGS)

ShockTower.o: $(SRC)/ShockTower.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/ShockTower.cpp $(LFLAGS)

SniperTower.o: $(SRC)/SniperTower.cpp
	$(CXX) $(CXXFLAGS) -c  $(SRC)/SniperTower.cpp $(LFLAGS)

run: compile
	./$(OUTPUT_BIN)/$(BIN)

doc:
	doxygen Doxyfile

clean:
	rm -f *.o $(OUTPUT_BIN)/$(BIN)
	
