//
// Created by yurunyang on 2021/10/26.
//

#include "iostream"
#include "fstream"
#include "vector"
#include "list"
#include "commonUtilis.h"
using namespace  std;


//this function is used to judge if this mesh has wrong shared edges
bool judgeSharedEdge(vector<string> &otherHalfEdges, ofstream *outputFile){

    vector<int> existedMap(otherHalfEdges.size(), 0);
    for(string halfEdge : otherHalfEdges){
        auto edgeData = strsplit(halfEdge," ");
        if(edgeData[2]=="-1"){      //if one halfEdge has no otherhalfEdge, then this mesh is not manifold
            *outputFile<<"halfEdge "<<edgeData[1]<<" has no otherhalf.\nEdge test Failed"<<endl;
            return false;
        }else{
            if(existedMap[atoi(edgeData[2].c_str())]==1){   //if one halfEdge has more than one edeg, than this mesh is not manifold
                *outputFile<<"halfedge "<<edgeData[1]<<" has more than one otherhalfEdge.\nEdge test Failed"<<endl;
                return false;
            }else{
                existedMap[atoi(edgeData[2].c_str())]=1;
            }
        }
    }
    *outputFile<<"edge test PASSED"<<endl;
    return true;

}


//this function is used to judge if these vertexs are pinch point.
//start from one vertex, put all faces that contain this vertex into a vector .
//Walking along the edges from one vertex to another vertex untill current vertex equal the original start vertex, and delete each face that visited
//Which means has find a circle of these faces.
//if the size of  facesWitheVertex is not zero, which means that there are more than one circle about this vertex.
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

//                    cout<<end<<"->";

                    breakFlag = true;
                    break;
                }
            }
            if(breakFlag)
                break;
        }
    }
    if(facesWitheVertex.size()!=0){
        return false;
    }
    return true;

}


bool judgePinchPoints(int vertexNum, vector<string> faces, ofstream* outputFile){
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
            *outputFile<<"vertex: "<<i<<" failed"<<endl;
            return false;
        }
//        cout<<"vertex "<<i<<" pass"<<endl;
    }

    return true;

}

int calculateGenus(vector<string> &vertexs, vector<string> &halfEdges, vector<string> &faces ){
    int vertexsNum = vertexs.size();
    int edgeNum = halfEdges.size()/2;
    int facesNum = faces.size();

    int genus = 1-(vertexsNum-edgeNum+facesNum)/2;
    return genus;


}



int main(int argc, char ** _argv){

    string inputFileName = _argv[1];
    ifstream *inputFile = new ifstream(inputFileName);
    if(!inputFile->is_open()){
        cout<<"File not existed"<<endl;
        return 0;
    }
    string outputFileName = inputFileName.substr(0,inputFileName.find_last_of('.'));
    ofstream *outputFile = new ofstream("manifoldResult",ios::app);
    *outputFile<<outputFileName<<endl;
    char buffer[100];
    vector<string> otherHalfEdges;
    vector<string> faces;
    vector<string> vertexs;
    while(inputFile->getline(buffer, 100)){
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

    bool result = judgeSharedEdge(otherHalfEdges, outputFile);
    if(result)
        result = judgePinchPoints(vertexs.size(), faces, outputFile);

    if(result){
        *outputFile<<"Manifold test PASSED"<<endl;
        int genus = calculateGenus(vertexs, otherHalfEdges, faces);
        *outputFile<<"The genus of this object is "<<genus<<endl;
    }
    else
        *outputFile<<"Manifold test FAILED"<<endl;


    *outputFile<<"============================================================"<<endl;

}
