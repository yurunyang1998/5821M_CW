question.a:./face2faceindex.cpp ./commonUtilis.h ./mesh.cpp
	g++ face2faceindex.cpp commonUtilis.h mesh.cpp -o questionA.o

question.b: ./faceindex2directededge.cpp ./commonUtilis.h
	g++ faceindex2directededge.cpp commonUtilis.h mesh.cpp -o questionB.o

question.c: ./manifoldClassify.cpp ./commonUtilis.h
	g++ manifoldClassify.cpp commonUtilis.h mesh.cpp -o questionC.o

clean:
	rm ./*.o