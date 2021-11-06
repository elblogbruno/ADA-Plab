#include "pch.h"
#include "Graph.h"
#include <vector>
#include <queue>
#include <stack>
#include <map>
using namespace std;

// =============================================================================
// SpanningTreePrim ============================================================
// =============================================================================

struct comparator {
	bool operator()(CEdge* pE1, CEdge* pE2) {
		return pE1->m_Length > pE2->m_Length;
	}
};

void MarcarPrim(CGraph& g, CVertex* pVertex, priority_queue<CEdge*, std::vector<CEdge*>, comparator>& queue, map<string, bool>& visitat)
{
	for (CVertex& v : g.m_Vertices) v.m_Marca = false;
	pVertex->m_Marca = true;
	for (CEdge* pE : pVertex->m_Edges) {
		if (!pE->m_pDestination->m_Marca) {
			queue.push(pE);
			pE->m_pDestination->m_Marca = true;
		}
	}
}

CSpanningTree SpanningTreePrim(CGraph& g)
{
	priority_queue<CEdge*, std::vector<CEdge*>, comparator> queue;

	CSpanningTree tree = CSpanningTree(&g);
	

	for (CEdge& v : g.m_Edges)
	{
		v.m_pDestination->m_Marca = false;

		if (v.m_pOrigin == &g.m_Vertices.front()) {
			queue.push(&v);
		}
	}

	g.m_Vertices.front().m_Marca = true;

	int numVertex = g.GetNVertices() - 1;
	

	while (!queue.empty() && numVertex != tree.GetNEdges())
	{
		CEdge* pE = queue.top();
		CVertex* pV = pE->m_pDestination;
		queue.pop();


		if (pV->m_Marca == false && pE->m_pOrigin->m_Marca == true)
		{
			pV->m_Marca = true;
			tree.m_Edges.push_back(pE);
			
			for (CEdge* pE1 : pV->m_Edges) {
				if (!pE1->m_pDestination->m_Marca && pE1->m_pOrigin->m_Marca && pE1->m_pDestination != pE->m_pOrigin) {
					queue.push(pE1);
				}
			}
		}
	}
	return tree;
}


