#include "Cartesian3.h"
#include "RGBAImage.h"
#include "DirectedEdgeSurface.h"
#include "subDivisionTools.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <set>
using namespace  std;


struct car3cmp{
bool operator()(const Cartesian3 &a)const{
    //std::cout<<a<<" "<<b<<std::endl;
    string keyName = std::to_string(a.x)+std::to_string(a.y)+std::to_string(a.z);
    return hash<string>()(keyName);

}

};

int updateHalfEdges(DirectedEdgeSurface *des){

    vector<Cartesian3>  vertices = des->vertices;
    vector<unsigned int>*  faceIndex = &(des->faceVertices);

    for(int i=0;i<faceIndex->size();i+=3){

        int vertex0Index = faceIndex->at(i);
        int vertex1Index = faceIndex->at(i+1);
        int vertex2Index = faceIndex->at(i+2);

        halfEdge e0(vertex2Index, vertex0Index);
        halfEdge e1(vertex0Index, vertex1Index);
        halfEdge e2(vertex1Index, vertex2Index);

        des->halfEdges.push_back(e0);
        des->halfEdges.push_back(e1);
        des->halfEdges.push_back(e2);

    }
    for(int i=0, k=1;i<des->halfEdges.size()-1, k<des->halfEdges.size();i++,k++){
        des->halfEdges[i].setNext(i+1);
    }
    des->halfEdges[des->halfEdges.size()-1].setNext(0);

    for(int i=0;i<des->otherHalf.size();i++){
        des->halfEdges[i].setPair(des->otherHalf[i]);
    }
    return 0;

}

int updateExistedVertex(DirectedEdgeSurface *des){

//    vector<Cartesian3> newVertexs;
    vector<Cartesian3>  vertices = des->vertices;
    for(int i=0;i<vertices.size();i++){

       set<int> linkedVertexs;
       for(auto halfEdge: des->halfEdges){

           if(halfEdge.startvextex()==i)
               linkedVertexs.insert(halfEdge.endvextex());
           else if(halfEdge.endvextex()==i)
               linkedVertexs.insert(halfEdge.startvextex());

       }

       float u =0.1;
       int n = linkedVertexs.size();
       Cartesian3 neighbor_position_sum(0,0,0);
       for(int neighbor: linkedVertexs){

           neighbor_position_sum.x += u* vertices[neighbor].x;
           neighbor_position_sum.y += u* vertices[neighbor].y;
           neighbor_position_sum.z += u* vertices[neighbor].z;

       }

       Cartesian3 newVertex = (1-n*u)*vertices[i] + neighbor_position_sum;
       des->existedVertexBuffer.push_back(newVertex);

    }
    return 0;


}




int subVertexs(DirectedEdgeSurface *des){
    
    unordered_map<Cartesian3, int, car3cmp> subVertexs;
    vector<unsigned int> newfaceVertices;
    vector<Cartesian3>  vertices = des->vertices;
    vector<unsigned int>*  faceIndex = &(des->faceVertices);
    for(int i=0;i<faceIndex->size();i+=3){


        auto vertex0Index = faceIndex->at(i);
        auto vertex1Index = faceIndex->at(i+1);
        auto vertex2Index = faceIndex->at(i+2);

        auto vertex0 = vertices[faceIndex->at(i)];
        auto vertex1 = vertices[faceIndex->at(i+1)];
        auto vertex2 = vertices[faceIndex->at(i+2)];


//        Cartesian3 vertex01((vertex0.x+vertex1.x)/2, (vertex0.y+vertex1.y)/2, (vertex0.z+vertex1.z)/2);
//        Cartesian3 vertex12((vertex1.x+vertex2.x)/2, (vertex1.y+vertex2.y)/2, (vertex1.z+vertex2.z)/2);
//        Cartesian3 vertex20((vertex2.x+vertex0.x)/2, (vertex2.y+vertex0.y)/2, (vertex2.z+vertex0.z)/2);


        Cartesian3 &A01 = vertex0;
        Cartesian3 &B01 = vertex1;
        Cartesian3 &D01 = vertex2;
        int j=0;
        while (!des->halfEdges[j].isEqual(vertex0Index, vertex1Index)) {
            j++;
        }
        int pairIndex = des->halfEdges[j].pairIndex;
        int nextIndex = des->halfEdges[pairIndex].next;
        int vertexCIndex = des->halfEdges[nextIndex].endvextex();
        Cartesian3 &C01 = des->vertices[vertexCIndex];
        Cartesian3 vertex01((A01.x+B01.x)/8*3+(C01.x+D01.x)/8,
                            (A01.y+B01.y)/8*3+(C01.y+D01.y)/8,
                            (A01.z+B01.z)/8*3+(C01.z+D01.z)/8
                    );




        Cartesian3 &A20 = vertex2;
        Cartesian3 &B20 = vertex0;
        Cartesian3 &D20 = vertex1;
        j=0;
        while (!des->halfEdges[j].isEqual(vertex2Index, vertex0Index)) {
            j++;
        }
        pairIndex = des->halfEdges[j].pairIndex;
        nextIndex = des->halfEdges[pairIndex].next;
        vertexCIndex = des->halfEdges[nextIndex].endvextex();
        Cartesian3 &C20 = des->vertices[vertexCIndex];
        Cartesian3 vertex20((A20.x+B20.x)/8*3+(C20.x+D20.x)/8,
                            (A20.y+B20.y)/8*3+(C20.y+D20.y)/8,
                            (A20.z+B20.z)/8*3+(C20.z+D20.z)/8
                    );




        Cartesian3 &A12 = vertex1;
        Cartesian3 &B12 = vertex2;
        Cartesian3 &D12 = vertex0;
        j=0;
        while (!des->halfEdges[j].isEqual(vertex1Index, vertex2Index)) {
            j++;
        }
        pairIndex = des->halfEdges[j].pairIndex;
        nextIndex = des->halfEdges[pairIndex].next;
        vertexCIndex = des->halfEdges[nextIndex].endvextex();
        Cartesian3 &C12 = des->vertices[vertexCIndex];
        Cartesian3 vertex12((A12.x+B12.x)/8*3+(C12.x+D12.x)/8,
                            (A12.y+B12.y)/8*3+(C12.y+D12.y)/8,
                            (A12.z+B12.z)/8*3+(C12.z+D12.z)/8
                    );
















//        std::cout<<vertex01<<std::endl;
        if(subVertexs.find(vertex01)==subVertexs.end()){
            vertices.push_back(vertex01);
            subVertexs.insert(make_pair(vertex01,vertices.size()-1));
        }

        auto iter= subVertexs.find(vertex12);
        if(iter==subVertexs.end()){
            vertices.push_back(vertex12);
            subVertexs.insert(make_pair(vertex12,vertices.size()-1));
        }
        iter= subVertexs.find(vertex20);
        if(iter==subVertexs.end()){
            vertices.push_back(vertex20);
            subVertexs.insert(make_pair(vertex20,vertices.size()-1));
        }

        int vertex01Index = subVertexs.find(vertex01)->second;
        int vertex12Index = subVertexs.find(vertex12)->second;
        int vertex20Index = subVertexs.find(vertex20)->second;


        //face 0-01-20
        newfaceVertices.push_back(faceIndex->at(i));
        newfaceVertices.push_back(vertex01Index);
        newfaceVertices.push_back(vertex20Index);

        //face 1-01-12
        newfaceVertices.push_back(faceIndex->at(i+1));
        newfaceVertices.push_back(vertex12Index);
        newfaceVertices.push_back(vertex01Index);

        //face 2-12-20
        newfaceVertices.push_back(faceIndex->at(i+2));
        newfaceVertices.push_back(vertex20Index);
        newfaceVertices.push_back(vertex12Index);

        //face 01-12-20
        newfaceVertices.push_back(vertex01Index);
        newfaceVertices.push_back(vertex12Index);
        newfaceVertices.push_back(vertex20Index);

    }
    
    des->vertices = vertices;
    des->faceVertices = newfaceVertices;





    return true;


}



int updateNormal(DirectedEdgeSurface *des){
    vector<Cartesian3> newNormal;
    vector<unsigned int> &faces = des->faceVertices;
    vector<Cartesian3> &vertexsIndex = des->vertices;

    for(int i=0;i<faces.size();i+=3){

        auto v0 = vertexsIndex[faces[i]];
        auto v1 = vertexsIndex[faces[i+1]];
        auto v2 = vertexsIndex[faces[i+2]];

        Cartesian3 edge01 = v0-v1;
        Cartesian3 edge02 = v0-v2;

//        Cartesian3 normal = edge02.cross(edge01).unit();
        Cartesian3 normal(0,0,0);
        newNormal.push_back(normal);

    }
    des->normals= newNormal;
    return 0;

}


















