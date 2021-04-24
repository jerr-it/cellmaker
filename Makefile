COMPILER = gcc
FLAGS = -g -std=c11 -pedantic -Wall -Werror -Wextra -Wfloat-equal -Wshadow


main: main.so automaton.so -lpthread
	${COMPILER} ${FLAGS} -o $@ $^

automaton.so: CellularAutomata/CellularAutomaton.c CellularAutomata/CellularAutomaton.h
	${COMPILER} ${FLAGS} -c -o $@ $<

main.so: main.c CellularAutomata/CellularAutomaton.h
	${COMPILER} ${FLAGS} -c -o $@ $<

clean: 
	rm -f main automaton.so main.so
