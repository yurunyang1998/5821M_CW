//
// Created by yurunyang on 2021/10/26.
//

#include "iostream"
#include "fstream"
#include "vector"
#include "list"
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

bool judgeSinglePoint(string vertexStr, list<string> facesWitheVertex){

    auto faceData = strsplit(facesWitheVertex.front(), " ");
    string start,end;
    for(int i=2;i<5;i++){
        if(faceData[i] == vertexStr){
            start = faceData[(i+1)%5];
            end = faceData[(i+2)%5];
        }
    }
    facesWitheVertex.pop_front();
    string anotherVertex = "";
    do{
        bool breakFlag = false;
        for(auto iter=facesWitheVertex.begin();iter!=facesWitheVertex.end();iter++){
            auto faceData = strsplit(*iter, " ");
            for(int i=2;i<5;i++){
                if(faceData[i]==end){
                    string anotherPoint1 = faceData[(i+1)%5];
                    string anotherPoint2 = faceData[(i+2)%5];
                    end = (anotherPoint1==vertexStr?anotherPoint2:anotherPoint1);
                    anotherVertex = (anotherPoint1==vertexStr?anotherPoint1:anotherPoint2);
                    facesWitheVertex.erase(iter);

                    cout<<end<<"->";

                    breakFlag = true;
                    break;
                }
            }
            if(breakFlag)
                break;
        }
    }while(anotherVertex!=start);
    if(facesWitheVertex.size()!=0){
        return false;
    }
    return true;




}


bool judgePinchPoints(int vertexNum, vector<string> faces){
    list<string> facesWitheVertex;
    for(int i=0;i<vertexNum;i++){
        string vertexStr = to_string(i);
        for(string face: faces){
            auto faceData = strsplit(face, " ");
            if(faceData[2]==vertexStr ||faceData[3]==vertexStr || faceData[4]==vertexStr ){
                facesWitheVertex.push_back(face);
            }
        }
        bool result = judgeSinglePoint(vertexStr, facesWitheVertex);
        if(result == false){
            return false;
        }

    }

    return true;

}

int main(){

    ifstream * inFile = new ifstream("./output.diredge");
    ofstream * outFile = new ofstream("./manifoldClassify");

    char buffer[100];
    vector<string> otherHalfEdges;
    vector<string> faces;
    vector<string> vertexs;
    while(inFile->getline(buffer, 100)){
        if(buffer[0] == 'O'){
            otherHalfEdges.push_back(string(buffer));
        }
        if(buffer[0] == 'F' and buffer[1] == 'a'){
            faces.push_back(string(buffer));
        }
        if(buffer[0] == 'V'){
            vertexs.push_back(string(buffer));
        }
    }

//    cout<<judgeSharedEdge(otherHalfEdges)<<endl;
    cout<<judgePinchPoints(vertexs.size(), faces)<<endl;

}
