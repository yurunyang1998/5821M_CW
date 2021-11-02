This project is the first Assignment of 5812.
this project provide with a makefile to compile three different output of question a b c d
(I combine question c d into same source file)

Following these steps to compile different target:
    "make question.a"  for question.a, it will generate a file named questionA.o
    run "questionA.o xxx.tri" to get the result of question.a, it will generate a face file under the ./output path
    for example run "questionA.o ./cow.tri", it will generate "./output/cow.face"

    "make question.b"  for question.b, it will generate a file named questionB.o
    run "questionB.o xxx.face" to get the result of question.b, it will generate a diredge file under "./output"
    for example run "questionB.o ./output/cow.face" ,it will generate "./output/cow.tri"

    "make question.b" for question.c and d , it will generate a file named questionC.o.
    run "questionC.o xxx.diredge" to get the result of question.c and d.
    It will generate the result of manifold test of the object and append it into the file named "manifoldResult".
    for example, run "questionC.o ./output/cow.diredge", it will append the result into manifoldResult.

Complexity Analysis
    for the question.a, function "vertex2IndexandFace" is the core function, it only need to iterate the vertexs once,
    then the complexity of this function is O(n).

    for the question.b, there are two loop paired , so the complexity is O(n^2)

    for the question.c and d, the complexity of "judgeSharedEdge" is O(n), and the complexity of "judgePinchPoints" are O(n),
    the complexity of "judgeSinglePoint" is O(n^2).Because "judgePinchPoints()" invoke "judgeSinglePoint", so the complexity of
    the "manifoldClassify.cpp" is O(n^3).
