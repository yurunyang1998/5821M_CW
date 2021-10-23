//
// Created by yurunyang on 2021/10/23.
//

#ifndef SOURCE_MESH_H
#define SOURCE_MESH_H

#include "vector"

using namespace std;
// The class of vextex
class Vextex{
public:
    float x,y,z;
    Vextex(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

class halfEdge{
private:
    vector<Vextex> * vextexIndex = nullptr;  // this is the pointer to the vextexIndex;
    int startVextexIndex = -1;
    int endVextexIndex = -1;  // the index of end vextex in vextexIndex;
public:
    halfEdge(int startVextexIndex, int endVextexIndex){
        this->startVextexIndex = startVextexIndex;
        this->endVextexIndex = endVextexIndex;
    }
    int startvextex(){
        return startVextexIndex;
    }
    int endvextex(){
        return endVextexIndex;
    }

};




class Mesh {
private:
    const vector<Vextex> * vextexIndex = nullptr;   //this is the point to vextexIndex
    const vector<halfEdge> * halfEdgeIndex = nullptr;    //this is the point to halfEdgesIndex;
    vector<int> vextexs;                            // this means the index of vextexs in vextexIndex
    vector<int> halfEdges;                          //this means the index of halfEdges in halfEdgesIndex

public:
    Mesh(const vector<Vextex>* vextexIndexPoint,const vector<halfEdge> * halfEdgeIndexPoint,
         vector<int> vextexs,vector<int> halfEdges){

        this->vextexIndex = vextexIndexPoint;
        this->halfEdgeIndex = halfEdgeIndexPoint;
        this->vextexs = vextexs;
        this->halfEdges = halfEdges;

    }



};


#endif //SOURCE_MESH_H
