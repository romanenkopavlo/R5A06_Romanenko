CC=g++
RM=rm -f
SRCS=ImageBase.cpp lodepng.cpp
CFLAGS = -g

motifs: clean
	${RM} motifs 
	${CC} ${CFLAGS} -o motifs motifs.cpp ${SRCS}

histo: clean
	${RM} histo 
	${CC} ${CFLAGS} -o histo histo.cpp ${SRCS}

stega: clean
	${RM} stega 
	${CC} ${CFLAGS} -o stega stega.cpp ${SRCS}

clean:
	${RM} *.o

