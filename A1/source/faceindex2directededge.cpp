//
// Created by yurunyang on 2021/10/22.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "mesh.cpp"
#include "commonUtilis.h"

using namespace std;

int face2halfEdges(vector<vector<int>> &faces, vector<halfEdge> * halfEdgesIndex){
    for(auto face:faces){

        halfEdge e0(face[0],face[1]); //initial a edge object
        halfEdge e1(face[1],face[2]);
        halfEdge e2(face[2],face[0]);

        halfEdgesIndex->push_back(e0);  // push edge into index
        halfEdgesIndex->push_back(e1);
        halfEdgesIndex->push_back(e2);

    }
    return 0;
}

vector<int> halfEdge2FistDirectedEdge(vector<halfEdge> &halfEdges, int vextexNum){
    vector<int> FirstDirectedEdges;
    for(int i=0;i<vextexNum;i++){
        for(int j=0;j<halfEdges.size();j++){
            if(halfEdges[j].endvextex()==i){
                FirstDirectedEdges.push_back(j);
                break;
            }
        }
    }

    return FirstDirectedEdges;


}


vector<int> findOtherHalfEdge(vector<halfEdge> &halfEdgesIndex){
    vector<int> otherHalfEdges;
    for(int i=0;i<halfEdgesIndex.size();i++){

        int start = halfEdgesIndex[i].startvextex();
        int end = halfEdgesIndex[i].endvextex();
        bool foundHalfEdge = false;
        for(int j=0;j<halfEdgesIndex.size();j++){
            if(halfEdgesIndex[j].endvextex()==start && halfEdgesIndex[j].startvextex()== end){
                otherHalfEdges.push_back(j);
                foundHalfEdge = true;
//                cout<<i<<":"<<halfEdgesIndex[i].startvextex()<<" "<<halfEdgesIndex[i].endvextex()<<"  ";
//                cout<<j<<":"<<halfEdgesIndex[j].startvextex()<<" "<<halfEdgesIndex[j].endvextex()<<endl;
                break;
            }
        }
        if(foundHalfEdge==false)
            otherHalfEdges.push_back(-1);
    }

    return otherHalfEdges;


}




int main(){

    ofstream *outputFile = new ofstream("./output.diredge");
    ifstream *inputFile = new ifstream("./test.face");

    char lineBuf[100];
    vector<Vextex> vextexIndex;
    vector<halfEdge> halfEdgeIndex;
    vector<vector<int>> faceIndex;
    while(inputFile->getline(lineBuf,100)){ // enumunate vextexs and faces
        if(lineBuf[0] == 'V')
        {
//            cout<<lineBuf<<endl;
            string str(lineBuf);  //convert char [] type to string
            vector<string> result = strsplit(str," ");
            float x = atof(result[2].c_str()); //convert string to float
            float y = atof(result[3].c_str());
            float z = atof(result[4].c_str());
//            cout<<x<<" "<<y<<" "<<z<<endl;
            Vextex vex(x,y,z);
            vextexIndex.push_back(vex);

        }
        else if(lineBuf[0]=='F'){
//            cout<<lineBuf<<endl;
            string str(lineBuf);
            vector<string> result = strsplit(str," ");
            int x = atoi(result[2].c_str()); //convert string to float
            int y = atoi(result[3].c_str());
            int z = atoi(result[4].c_str());
//            cout<<x<<" "<<y<<" "<<z<<endl;
            vector<int> face = {x,y,z};
            faceIndex.push_back(face);
        }




    }

    face2halfEdges(faceIndex, &halfEdgeIndex);

    auto FDE = halfEdge2FistDirectedEdge(halfEdgeIndex, vextexIndex.size());
    auto otherHalfEdge = findOtherHalfEdge(halfEdgeIndex);
    for(int i=0;i<otherHalfEdge.size();i++){
        cout<<i<<" "<<otherHalfEdge[i]<<endl;
    }






}
