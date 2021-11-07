#include "pch.h"
#include "Graph.h"

// SalesmanTrackGreedy =========================================================

CTrack ShortestPath(CGraph& graph, CVertex* begin, CVertex* end) {
	CTrack path = CTrack(&graph);

	/*
		Node Inici i node final estan directament connectats per un sol edge.
	*/
	if (graph.MemberP(begin, end)) {
		path.AddFirst(graph.FindEdge(begin, end));
	}
	else {
		/*
			Comencem desde el vertex final cap al inici, mirant de edge en edge fins que arrivem al edge d'inici.
		*/

		CVertex* vertex = end;
		while (vertex->m_Name != begin->m_Name) {
			for (CEdge* edge : vertex->m_Edges) {
				if (vertex == edge->m_pDestination) {
					if (vertex->m_DijkstraDistance < edge->m_Length + edge->m_pOrigin->m_DijkstraDistance + 0.0001 && vertex->m_DijkstraDistance > edge->m_Length + edge->m_pOrigin->m_DijkstraDistance - 0.0001) {
						path.AddFirst(edge->m_pReverseEdge);
						vertex = edge->m_pOrigin;
					}
				}
				else if (vertex == edge->m_pOrigin) {
					if (vertex->m_DijkstraDistance < edge->m_Length + edge->m_pDestination->m_DijkstraDistance + 0.0001 && vertex->m_DijkstraDistance > edge->m_Length + edge->m_pDestination->m_DijkstraDistance - 0.0001) {
						path.AddFirst(edge->m_pReverseEdge);
						vertex = edge->m_pDestination;
					}
				}
			}
		}
	}
	return path;
}
// SalesmanTrackGreedy =========================================================

/*

1. Començar per la ciutat d'origen
2. Mentre hi hagi ciutats per visitar excepte la ciutat destí repetir:
a. Cercar quina és la ciutat de les que hem de visitar més propera a la que estem
(en aquesta cerca no incloem la ciutat destí ja que sempre ha de ser l'última a la
que es vagi)
b. Anar a la ciutat més propera
c. Treure la ciutat on estem de les que hem de visitar
3. Anar a la ciutat destí.

*/

CTrack SalesmanTrackGreedy(CGraph& graph, CVisits &visits)
{
	CTrack track = CTrack(&graph);
	CVertex* v = visits.m_Vertices.front();
	
	/*
		Nodes candidats son aquelles ciutats que hem de visitar, hem de eliminar la ciutat d'origen i la de desti.
	*/
	vector<CVertex*> candidats;

	for (CVertex* a : visits.m_Vertices) {
		if (a != visits.m_Vertices.front() && a != visits.m_Vertices.back()) {
			candidats.push_back(a);
		}
	}
	
	CVertex* v1 = v; // 1. començem per la ciutat d'origen

	while (!candidats.empty()) { // 2. Mentre hi hagi ciutats per visitar excepte la ciutat destí repetir:

		/* a. Calculem distancies amb dijkstra per trobar la ciutat mes propera a la que estem ara*/
		DijkstraQueue(graph, v);
		double minimum = numeric_limits<double>::max();
		

		for (CVertex* b : candidats) {
			if (b->m_DijkstraDistance < minimum) {
				v1 = b;
				minimum = b->m_DijkstraDistance;
			}
		}
		
		track.Append(ShortestPath(graph, v, v1)); 

		v = v1; // b. Anar a la ciutat més propera

		/*
		c. Treure la ciutat on estem de les que hem de visitar
		*/

		if (candidats.size() == 1) {
			candidats.clear();
		}
		else {
			auto it = candidats.begin();
			while (it != candidats.end()) {
				if ((*it)->m_Name != v1->m_Name) {
					it++;
				}
				else {
					swap(*it, candidats.back());
					candidats.pop_back();
					break;
				}
			}
		}

	}

	/* Ens queda el ultim troç entre la penultima ciutat i la ciutat desti*/

	DijkstraQueue(graph, v);
	
	track.Append(ShortestPath(graph, v, visits.m_Vertices.back()));
	
	return track;
}
