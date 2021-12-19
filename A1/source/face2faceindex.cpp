#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <array>
#include <string>
#include "commonUtilis.h"
using namespace std;

//This function is used to de-duplication of vertexs and convert it into index. and combine every three vertexs to a face.
vector<array<int,3>> vertex2IndexandFace(vector<string> &vertexs,vector<string> &vertexIndex){
    unordered_map<string, int> vertexMap; // this map is to find if this vertex has appeared before.
    vector<array<int,3>> facesIndex;
    int i=0;
    while(i<vertexs.size()){  //iterate the whole vertesx vector
        array<int,3> face;
        int pointIndex = 0;
        for(int j=0;j<3;j++,i++){
            auto iter = vertexMap.find(vertexs[i]);
            if(iter == vertexMap.end()){  // can't find this vertex in map, means that this vertex has not been visited before.
                vertexIndex.push_back(vertexs[i]);  // push this vertex into index
                vertexMap.insert(make_pair(vertexs[i], vertexIndex.size()-1)); //update the map
                pointIndex = vertexIndex.size()-1;
            }else{
                pointIndex = iter->second;
            }
            face[j] = pointIndex; // set the index of vertex  of the face as the index of this vertex
        }
        facesIndex.push_back(face);     //push the face into faceIndex
    }
    cout<<vertexIndex.size()<<endl;
    return facesIndex;

}


int main(int argc, char ** _argv) {


    string inputFileName = _argv[1];
    ifstream *inputFile = new ifstream(inputFileName);
    if(!inputFile->is_open()){
        cout<<"File not existed"<<endl;
        return 0;
    }

    string outputFileName = inputFileName.substr(0,inputFileName.find_last_of('.')); // get the file name without suffix
    outputFileName = outputFileName.substr(outputFileName.find_last_of('/'));
    outputFileName = "./output/"+outputFileName+".face";
    cout<<outputFileName<<endl;
    ofstream *outputFile = new ofstream(outputFileName);


    char faceNumBuf[5];
    inputFile->getline(faceNumBuf,10);
    int faceNum = atoi(faceNumBuf);
    vector<string> vertexs;
    vector<string> vertexsIndex;
    char vertexBuf[100];
    for(int i=0;i<faceNum*3;i++){
        inputFile->getline(vertexBuf,100);
        vertexs.push_back(string(vertexBuf));     // put the string data into a vector
    }

    auto faces = vertex2IndexandFace(vertexs, vertexsIndex);
    int verticesNum = vertexsIndex.size();
    int facesNum= faces.size();
    string header = "# University of Leeds 2020-2021\n"
                    "# COMP 5812M Assignment 1\n"
                    "# runyang yu\n"
                    "# 201480588\n"
                    "#\n"
                    "# Object Name: "+ outputFileName+"\n"
                    "# Vertices="+to_string(verticesNum)+"Faces=" +to_string(facesNum)+" \n#";

    appendHeader(outputFile, header);   //output the header into file
    for(int i=0;i<vertexsIndex.size();i++){
        *outputFile<<"Vertex "<<i<<" "<<vertexsIndex[i]<<endl;
    }
    for(int i=0;i<faces.size();i++){
        *outputFile<<"Face "<<i<<" "<<faces[i][0]<<" "<<faces[i][1]<<" "<<faces[i][2]<<endl;
    }
    outputFile->close();
}
