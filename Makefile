CXX = g++
CXXFLAGS = -Wall -MMD -std=c++0x
EXEC = trieDict
OBJECTS = main.o trie.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
