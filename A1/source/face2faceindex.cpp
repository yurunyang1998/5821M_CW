#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <array>
#include <string>
#include "commonUtilis.h"
using namespace std;


vector<array<int,3>> vextex2IndexandFace(vector<string> &vextexs,vector<string> &vextexIndex){
    unordered_map<string, int> vextexMap;
    vector<array<int,3>> facesIndex;
    int i=0;
    while(i<vextexs.size()){
        array<int,3> face;
        int pointIndex = 0;
        for(int j=0;j<3;j++,i++){
            auto iter = vextexMap.find(vextexs[i]);
            if(iter == vextexMap.end()){
                vextexIndex.push_back(vextexs[i]);
                vextexMap.insert(make_pair(vextexs[i], vextexIndex.size()-1));
                pointIndex = vextexIndex.size()-1;
            }else{
                pointIndex = iter->second;
            }
            face[j] = pointIndex;
        }
        facesIndex.push_back(face);
    }
    cout<<vextexIndex.size()<<endl;
    return facesIndex;

}


int main() {


    string inputFileName = _argv[1];
    ifstream *inputFile = new ifstream(inputFileName);
    if(!inputFile->is_open()){
        cout<<"File not existed"<<endl;
        return 0;
    }
    string outputFileName = inputFileName.substr(0,inputFileName.find_last_of('.'));
    cout<<outputFileName<<endl;
    ofstream *outputFile = new ofstream(outputFileName+".face");


    char faceNumBuf[5];
    inputFile->getline(faceNumBuf,10);
    int faceNum = atoi(faceNumBuf);
    vector<string> vertexs;
    vector<string> vertexsIndex;
    char vertexBuf[100];
    for(int i=0;i<faceNum*3;i++){
        inputFile->getline(vertexBuf,100);
        vertexs.push_back(string(vertexBuf));
    }

    auto faces = vextex2IndexandFace(vertexs, vertexsIndex);
    int verticesNum = vertexsIndex.size();
    int facesNum= faces.size();
    string header = "# University of Leeds 2020-2021\n"
                    "# COMP 5812M Assignment 1\n"
                    "# runyang yu\n"
                    "# 201480588\n"
                    "#\n"
                    "# Object Name: Cube\n"
                    "# Vertices="+to_string(verticesNum)+"Faces=" +to_string(facesNum)+" \n#";

    appendHeader(outputFile, header);
    for(int i=0;i<vertexsIndex.size();i++){
        *outputFile<<"Vertex "<<i<<" "<<vertexsIndex[i]<<endl;
    }
    for(int i=0;i<faces.size();i++){
        *outputFile<<"Face "<<i<<" "<<faces[i][0]<<" "<<faces[i][1]<<" "<<faces[i][2]<<endl;
    }
    outputFile->close();
}
