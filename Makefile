CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = tt.out
OBJECTS = main.o #command.o field.o tetromino.o IBlock.o JBlock.o LBlock.o ZBlock.o SBlock.o TBlock.o OBlock.o window.o colour.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -L/usr/X11R6/lib -lX11 -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
