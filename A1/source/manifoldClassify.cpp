//
// Created by yurunyang on 2021/10/26.
//

#include "iostream"
#include "fstream"
#include "vector"
#include "commonUtilis.h"
using namespace  std;

bool judgeSharedEdge(vector<string> &otherHalfEdges){

    vector<int> existedMap(otherHalfEdges.size(), 0);
    for(string halfEdge : otherHalfEdges){
        auto edgeData = strsplit(halfEdge," ");
        if(edgeData[2]=="-1"){
            return false;
        }else{
            if(existedMap[atoi(edgeData[2].c_str())]==1){
                return false;
            }else{
                existedMap[atoi(edgeData[2].c_str())]=1;
            }
        }
    }
    return true;

}

bool judgeSinglePoint(string vertexStr, vector<string> facesWitheVertex){

    auto faceData = strsplit(facesWitheVertex[0], " ");
    for(int i=2;i<5;i++){
        if(faceData[i] == vertexStr){
            
        }
    }



}


bool judgePinchPoints(int vertexNum, vector<string> faces){
    vector<string> facesWitheVertex;
    for(int i=0;i<vertexNum;i++){
        for(string face: faces){
            auto faceData = strsplit(face, " ");
            string vertexStr = to_string(i);
            if(faceData[2]==vertexStr ||faceData[3]==vertexStr || faceData[4]==vertexStr ){
                facesWitheVertex.push_back(face);
            }
        }


    }



}

int main(){

    ifstream * inFile = new ifstream("./output.diredge");
    ofstream * outFile = new ofstream("./manifoldClassify");

    char buffer[100];
    vector<string> otherHalfEdges;
    while(inFile->getline(buffer, 100)){
        if(buffer[0] == 'O'){
            otherHalfEdges.push_back(string(buffer));
        }
    }

    cout<<judgeSharedEdge(otherHalfEdges)<<endl;


}
