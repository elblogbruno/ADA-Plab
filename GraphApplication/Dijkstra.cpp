#include "pch.h"
#include "Graph.h"
#include <queue>


void inicialitzaVertexs(CGraph& graph)
{
	for (list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); it++) {
		it->m_DijkstraDistance = numeric_limits<double>::max();
		it->m_DijkstraVisit = false;
	}
}

int minDistance(CGraph& graph) {
	double min_distance = INFINITY;
	int index = -1;
	for (list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); it++) {
		if (it->m_DijkstraDistance < min_distance && it->m_DijkstraVisit == false) {
			min_distance = it->m_DijkstraDistance;
			index = distance(graph.m_Vertices.begin(), it);
		}
	}
	return index;
}


/*
	Primer vam trobar que la funció GetVertex feia retrasar el nostre algorisme, per aixó aquesta funció retorna directament l'objecte en
	lloc del index com a la funció minDistance a sobre, aixi no fa falta utilitzar la funcio GetVertex(index)
*/

CVertex* minDistanceFaster(CGraph& graph) {
	double min_distance = INFINITY;
	CVertex* index = NULL;
	for (list<CVertex>::iterator it = graph.m_Vertices.begin(); it != graph.m_Vertices.end(); it++) {
		if (it->m_DijkstraDistance < min_distance && it->m_DijkstraVisit == false) {
			min_distance = it->m_DijkstraDistance;
			index = &(*it);
		}
	}
	return index;
}

// =============================================================================
// Dijkstra ====================================================================
// =============================================================================

void Dijkstra(CGraph& graph, CVertex* pStart)
{
	// Inicialització del Graf
	
	for (CVertex& v : graph.m_Vertices) {
		v.m_DijkstraDistance = numeric_limits<double>::max();
		v.m_DijkstraVisit = false;
	}

	pStart->m_DijkstraDistance = 0;
	pStart->m_DijkstraVisit = true;

	int min_index = 0;
	auto pActual = pStart;

	while (true) {
		pActual->m_DijkstraVisit = true;
		
		for (CEdge* v : pActual->m_Edges) {
			double edge_length = v->m_Length;
			double pActual_distance = pActual->m_DijkstraDistance + edge_length;
			if (v->m_pDestination->m_DijkstraDistance > pActual_distance) {
				v->m_pDestination->m_DijkstraDistance = pActual_distance;
			}
		}

		pActual = minDistanceFaster(graph);
		
		if (pActual == NULL) {
			break;
		}

	}
}

struct MyStruct
{
	CVertex* pV1;
	double m_DijkstraDistance;
};


// =============================================================================
// DijkstraQueue ===============================================================
// =============================================================================

void DijkstraQueue(CGraph& graph, CVertex* pStart)
{
	inicialitzaVertexs(graph);

	struct comparator {
		bool operator()(MyStruct pV1, MyStruct pV2) {
			return pV1.m_DijkstraDistance > pV2.m_DijkstraDistance;
		}
	};
	priority_queue<MyStruct, std::vector<MyStruct>, comparator> queue;

	struct MyStruct start;
	pStart->m_DijkstraDistance = 0;
	pStart->m_DijkstraVisit = true;

	start.m_DijkstraDistance = 0;
	start.pV1 = pStart;

	queue.push(start);

	while (!queue.empty()) {
		MyStruct pActual = queue.top();
		pActual.pV1->m_DijkstraVisit = true;
		queue.pop();

		for (list<CEdge*>::iterator it = pActual.pV1->m_Edges.begin(); it != pActual.pV1->m_Edges.end(); it++) {
			
			double edge_length = (*it)->m_Length;
			double pActual_distance = pActual.m_DijkstraDistance + edge_length;
			if ((*it)->m_pDestination->m_DijkstraDistance > pActual_distance) {
				(*it)->m_pDestination->m_DijkstraDistance = pActual_distance;
				
				if (!(*it)->m_pDestination->m_DijkstraVisit) {
					struct MyStruct start;
					
					start.m_DijkstraDistance = pActual_distance;
					start.pV1 = (*it)->m_pDestination;
					queue.push(start);
				}
			}
		}
	}


}