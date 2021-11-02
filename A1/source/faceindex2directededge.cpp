//
// Created by yurunyang on 2021/10/22.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "mesh.cpp"
#include "commonUtilis.h"

using namespace std;


//this function is used to generate halfEdges data from faces data
int face2halfEdges(vector<vector<int>> &faces, vector<halfEdge> * halfEdgesIndex){
    for(auto face:faces){
        //generate halfedge from face
        halfEdge e0(face[0],face[1]); //initial a edge object
        halfEdge e1(face[1],face[2]);
        halfEdge e2(face[2],face[0]);

        halfEdgesIndex->push_back(e0);  // push edge into index
        halfEdgesIndex->push_back(e1);
        halfEdgesIndex->push_back(e2);

    }
    return 0;
}

//generate FirstDirectedEdge from halfEdge
vector<int> halfEdge2FistDirectedEdge(vector<halfEdge> &halfEdges, int vextexNum){
    vector<int> FirstDirectedEdges;
    for(int i=0;i<vextexNum;i++){       //iterate each vertexs and each halfEdges, if the endvertex of the halfEdge is same to the this vertex,
        for(int j=0;j<halfEdges.size();j++){    // so the firstDirectedEdge of this vertex is this halfEdge
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
            //if two halfEdges' startpoint and endpoint are reverse, these two halfEdges are pair.
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




int main(int argc, char ** _argv){

    string inputFileName = _argv[1];
    ifstream *inputFile = new ifstream(inputFileName);
    if(!inputFile->is_open()){ // juduge whether this file existed
        cout<<"File not existed"<<endl;
        return 0;
    }
    string outputFileName = inputFileName.substr(0,inputFileName.find_last_of('.'));
    outputFileName = outputFileName.substr(outputFileName.find_last_of('/'));
    cout<<outputFileName<<endl;
    string outputPath = "./output/"+outputFileName+".diredge";
    cout<<outputPath<<endl;
    ofstream *outputFile = new ofstream(outputPath);



    char lineBuf[100];
    vector<Vextex> vextexIndex;
    vector<string> vextexsBuffer;
    vector<halfEdge> halfEdgeIndex;
    vector<vector<int>> faceIndex;
    vector<string> facesBuffer;
    while(inputFile->getline(lineBuf,100)){ // enumunate vextexs and faces
        if(lineBuf[0] == 'V')   //the first alpha of the vertexs data is 'V'
        {
//            cout<<lineBuf<<endl;
            string str(lineBuf);  //convert char [] type to string
            vextexsBuffer.push_back(str);
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
            facesBuffer.push_back(str);
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

    vector<int> FDE = halfEdge2FistDirectedEdge(halfEdgeIndex, vextexIndex.size());
    vector<int> otherHalfEdge = findOtherHalfEdge(halfEdgeIndex);

    string  header = "# University of Leeds 2020-2021\n"
                                    "# COMP 5812M Assignment 1\n"
                                    "# runyang yu\n"
                                    "# 201480588\n"
                                    "#\n"
                                    "# Object Name: "+outputFileName+"\n"
                                    "# Vertices="+to_string(vextexsBuffer.size())+"Faces=" +to_string(facesBuffer.size())+" \n#";

    appendHeader(outputFile, header);
    for(string vextex: vextexsBuffer){
        *outputFile<<vextex<<"\n";
    }
    for(int i=0;i<FDE.size();i++){
        *outputFile<<"FirstDirectedEdge "<<i<<" "<<FDE[i]<<'\n';
    }
    for(string face:facesBuffer){
        *outputFile<<face<<'\n';
    }
    for(int i=0;i<otherHalfEdge.size();i++){
        *outputFile<<"OtherHalf "<<i<<" "<<otherHalfEdge[i]<<'\n';
    }

    outputFile->close();
    inputFile->close();

}
