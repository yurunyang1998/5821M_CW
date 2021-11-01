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
            if(i==2){
                start = faceData[3];
                end = faceData[4];
            }else if(i==3){
                start = faceData[4];
                end = faceData[2];
            }else if(i==4){
                start = faceData[2];
                end = faceData[3];
            }
        }

    }
    facesWitheVertex.pop_front();
    string anotherVertex = "";
    auto iter=facesWitheVertex.begin();
    while(end!=start && iter!=facesWitheVertex.end()){
        bool breakFlag = false;
        for(iter=facesWitheVertex.begin();iter!=facesWitheVertex.end();iter++){
            auto faceData = strsplit(*iter, " ");
            for(int i=2;i<5;i++){
                if(faceData[i]==end){
                    string anotherPoint1;// = faceData[(i+1)%5];
                    string anotherPoint2;// = faceData[(i+2)%5];
                    if(i==2){
                        anotherPoint1 = faceData[3];
                        anotherPoint2 = faceData[4];
                    }else if(i==3){
                        anotherPoint1 = faceData[4];
                        anotherPoint2 = faceData[2];
                    }else if(i==4){
                        anotherPoint1 = faceData[2];
                        anotherPoint2 = faceData[3];
                    }

                    end = (anotherPoint1==vertexStr?anotherPoint2:anotherPoint1);
                    facesWitheVertex.erase(iter);

                    cout<<end<<"->";

                    breakFlag = true;
                    break;
                }
            }
            if(breakFlag)
                break;
        }
//        break;
    }
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
        facesWitheVertex.clear();
        if(result == false){
            return false;
        }
        cout<<"point "<<i<<" pass"<<endl;
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
    bool result = judgePinchPoints(vertexs.size(), faces);
    if(result)
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
}
