#include "pch.h"
#include "Graph.h"
#include <set>


// =============================================================================
// SalesmanTrackBacktracking ===================================================
// =============================================================================

void BacktrackingRecursiu(CGraph& graph, CVisits& visits, CVertex* pActual, CVertex* pDesti, CTrack* optTrack) {
	
	bool belongsVisits;

	for (CEdge* e : pActual->m_Edges) {
		if (visits.m_Vertices.empty() && e->m_pDestination->m_Point == pDesti->m_Point) {
			return;
		}
		else if (!visits.m_Vertices.empty() || e->m_pDestination->m_Point != pDesti->m_Point) {
			//if (getBelongingPath(e->m_pDestination, stackTrack) != actNodePathID) {
				//nextNode = new CNode(e->m_pDestination, actNodePathID);
				//nextNode->setEdgePath(e);
				belongsVisits = visits.MemberP(e->m_pDestination);

				if (belongsVisits) {
					//nextNode->setPathID(nextNode->getPathID() + 1);
					visits.m_Vertices.remove(e->m_pDestination);
				}
				
				BacktrackingRecursiu(graph, visits, e->m_pDestination, pDesti, optTrack);

				if (belongsVisits) {
					//nextNode->setPathID(actNodePathID);
					visits.Add(e->m_pDestination);
					optTrack->AddLast(e);
				}
			//}
		}
	}


}

CTrack SalesmanTrackBacktracking(CGraph &graph, CVisits &visits)
{
	CVisits visitsCopy = visits;
	CTrack* optTrack = new CTrack(&graph);
	
	BacktrackingRecursiu(graph, visitsCopy, &graph.m_Vertices.front(), visits.m_Vertices.back(), optTrack);

	return *optTrack;
}


// =============================================================================
// SalesmanTrackBacktrackingGreedy =============================================
// =============================================================================

// Funció per inicialitza la matriu amb les distancies de tots els parells de vertexs a visitar
/*
vector<vector<double>> InicialitzaMatrix(CGraph& graph, CVisits& visits)
{
	vector<vector<double>> distance_matrix;	// Definim vector
	// Fem resize amb NxN on N=nº de nodes a visitar
	distance_matrix.resize(visits.GetNVertices(), vector<double>(visits.GetNVertices())); 

	int row = 0;
	int col = 0;
	for (CVertex* vertex : visits.m_Vertices) {
		// Cridem Dijkstra per a cada node del Graph
		DijkstraQueue(graph, vertex);	

		// Per a cada node de la fila el guardem a la matriu de distància
		for (CVertex* vertex_2 : visits.m_Vertices) {
			distance_matrix[row][col] = vertex_2->m_DijkstraDistance;
			col++;
		}
		col = 0; row++;
	}
	return distance_matrix;
}
*/

vector<CTrack*> CreateTrack(CGraph &graph, CVertex* vertex_desti, CVisits& visits) {
	vector <CTrack*> track_vector;

	for (CVertex* vertex : visits.m_Vertices) {		// Per a cada node a visitar
		CVertex* pVertexActual = vertex;
		CTrack* track = new CTrack(&graph);

		while (pVertexActual != vertex_desti) {
			// track->AddLast(pVertexActual->m_DijkstraAnterior); // Afegim l'aresta anterior de Dijkstra
			track->AddFirst(pVertexActual->m_DijkstraAnterior);
			pVertexActual = pVertexActual->m_DijkstraAnterior->m_pOrigin;
		}
		track_vector.push_back(track);
	}

	return track_vector;
}

struct Index
{
	int i;
	int j;
};

/*
int getMinDistance(vector<vector<double>> const distance_matrix, int const row) {
	int index = -1;
	double min_distance = INFINITY;
	for (double distance : distance_matrix[row]) {
		if(distance)
	}
	return 
}
*/

CTrack SalesmanTrackBacktrackingGreedyRecursiu(vector<vector<CTrack*>> track_matrix, vector<vector<double>> distance_matrix, Index index_actual, vector<CTrack*> track_list) {
	// track_matrix = Info taulell de camins
	// distance_matrix = Info taulel de distancies
	// track_list = Vector amb el resultat



	return CTrack(NULL);
}

CTrack SalesmanTrackBacktrackingGreedy(CGraph& graph, CVisits& visits)
{
	// Definim vector distàncies i camins
	vector<vector<double>> distance_matrix;	
	vector<vector<CTrack*>> track_matrix;

	// Fem resize amb NxN on N=nº de nodes a visitar
	distance_matrix.resize(visits.GetNVertices(), vector<double>(visits.GetNVertices()));
	track_matrix.resize(visits.GetNVertices(), vector<CTrack*>(visits.GetNVertices()));

	int row = 0;
	int col = 0;
	for (CVertex* vertex : visits.m_Vertices) {
		// Cridem Dijkstra per a cada node del Graph
		DijkstraQueue(graph, vertex);
		// Per a cada node de la fila el guardem a la matriu de distància i matriu track
		track_matrix[row] = CreateTrack(graph, vertex, visits);
		for (CVertex* vertex_2 : visits.m_Vertices) {
			distance_matrix[row][col] = vertex_2->m_DijkstraDistance;
			CTrack* track = new CTrack(&graph);
			col++;
		}
		col = 0; row++;
	}
	return CTrack(&graph);
}
