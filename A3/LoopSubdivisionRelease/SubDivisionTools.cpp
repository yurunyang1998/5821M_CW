#include "Cartesian3.h"
#include "RGBAImage.h"
#include "DirectedEdgeSurface.h"
#include "subDivisionTools.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

using namespace  std;


struct car3cmp{
bool operator()(const Cartesian3 &a)const{
    //std::cout<<a<<" "<<b<<std::endl;
    string keyName = std::to_string(a.x)+std::to_string(a.y)+std::to_string(a.z);
    return hash<string>()(keyName);

}

};


int subVertexs(DirectedEdgeSurface *des){
    
    unordered_map<Cartesian3, int, car3cmp> subVertexs;
    vector<unsigned int> newfaceVertices;
    vector<Cartesian3>  vertices = des->vertices;
    vector<unsigned int>*  faceIndex = &(des->faceVertices);
    for(int i=0;i<faceIndex->size();i+=3){

        auto vertex0 = vertices[faceIndex->at(i)];
        auto vertex1 = vertices[faceIndex->at(i+1)];
        auto vertex2 = vertices[faceIndex->at(i+2)];

//        auto vertex0 = vertices[faceIndex[i]];
//        auto vertex1 = vertices[faceIndex[i+1]];
//        auto vertex2 = vertices[faceIndex[i+2]];
        
        Cartesian3 vertex01((vertex0.x+vertex1.x)/2, (vertex0.y+vertex1.y)/2, (vertex0.z+vertex1.z)/2);
        Cartesian3 vertex12((vertex1.x+vertex2.x)/2, (vertex1.y+vertex2.y)/2, (vertex1.z+vertex2.z)/2);
        Cartesian3 vertex20((vertex2.x+vertex0.x)/2, (vertex2.y+vertex0.y)/2, (vertex2.z+vertex0.z)/2);

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
        newfaceVertices.push_back(vertex01Index);
        newfaceVertices.push_back(vertex12Index);

        //face 2-12-20
        newfaceVertices.push_back(faceIndex->at(i+2));
        newfaceVertices.push_back(vertex12Index);
        newfaceVertices.push_back(vertex20Index);

        //face 01-12-20
        newfaceVertices.push_back(vertex01Index);
        newfaceVertices.push_back(vertex12Index);
        newfaceVertices.push_back(vertex20Index);

    }
    
    des->vertices = vertices;
    des->faceVertices = newfaceVertices;
    return true;


}






















