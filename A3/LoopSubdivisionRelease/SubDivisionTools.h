#ifndef SUBDIVISIONTOOLS_H
#define SUBDIVISIONTOOLS_H

#include <DirectedEdgeSurface.h>
#include <vector>





int subVertexs(DirectedEdgeSurface *des);


int updateNormal(DirectedEdgeSurface *des);

int updateHalfEdges(DirectedEdgeSurface *des);

int updateExistedVertex(DirectedEdgeSurface *des);

int findOtherHalfEdge(std::vector<halfEdge> &halfEdgesIndex, std::vector<int> &otherHalfEdges);



#endif // SUBDIVISIONTOOLS_H
