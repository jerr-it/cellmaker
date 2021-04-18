COMPILER = gcc
FLAGS = -g 


main: main.o automaton.o
	${COMPILER} -o $@ $^

automaton.o: CellularAutomata/CellularAutomaton.c CellularAutomata/CellularAutomaton.h
	${COMPILER} ${FLAGS} -c -o $@ $<

main.o: main.c CellularAutomata/CellularAutomaton.h
	${COMPILER} ${FLAGS} -c -o $@ $<

clean: 
	rm -f main automaton.o main.o