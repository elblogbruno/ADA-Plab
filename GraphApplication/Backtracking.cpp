#include "pch.h"
#include "Graph.h"
#include <set>


// =============================================================================
// SalesmanTrackBacktracking ===================================================
// =============================================================================

void BacktrackingRecursiu(CGraph& graph, CVisits& visits, CVertex* pActual, CVertex* pDesti, CTrack* finalTrack) {
	
	bool belongsVisits;

	/*if (pActual == pDesti && visits.m_Vertices.empty()) 
		*finalTrack = *actTrack;*/
	// pas endavant
	if (finalTrack->Length() == 0 && visits.GetNVertices() > 0) {
		for (CEdge* e : pActual->m_Edges) { // Per a cada veí del vèrtex actual veure si es pot passar per ell

			if (visits.m_Vertices.empty() && e->m_pDestination->m_Point == pDesti->m_Point) {
				BacktrackingRecursiu(graph, visits, pDesti, pDesti, finalTrack);
			}
			else if (!visits.m_Vertices.empty() || e->m_pDestination->m_Point != pDesti->m_Point) {
				//if (getBelongingPath(e->m_pDestination, stackTrack) != actNodePathID) {
				belongsVisits = visits.MemberP(e->m_pDestination);

				if (belongsVisits) {
					visits.m_Vertices.remove(e->m_pDestination);
				}

				BacktrackingRecursiu(graph, visits, e->m_pDestination, pDesti, finalTrack);

				//  fem el pas enrere
				if (belongsVisits) {
					//nextNode->setPathID(actNodePathID);
					visits.Add(e->m_pDestination);
					finalTrack->AddLast(e);
				}
				//}
			}
		}
	}

}

CTrack SalesmanTrackBacktracking(CGraph &graph, CVisits &visits)
{
	CVisits visitsCopy = visits;
	CTrack* finalTrack = new CTrack(&graph);
	
	BacktrackingRecursiu(graph, visitsCopy, &graph.m_Vertices.front(), visits.m_Vertices.back(), finalTrack);

	return *finalTrack;
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

void SalesmanTrackBacktrackingGreedyRecursiu(vector<vector<double>>& distance_matrix, vector<int>& indexVertexsOptims, int index_actual, vector<int>& indexVertexsAVisitar, double* distanciaOptima, double* distanciaActual, vector<bool>& boolVertexsVisitats) {
	// distance_matrix = Info taulel de distancies
	// indexVertexsOptims = Llista d'indexs que formen el cami optim
	// index_actual = Posicio actual
	// indexVertexsAVisitar = Llista dels index que s'han de visitar
	
	indexVertexsAVisitar.push_back(index_actual);		// Afegim al cami el node a visitar
	boolVertexsVisitats[index_actual] = true;			// El marquem com a visitat

	// Si no es sol.lució completa, llavors:
	if (indexVertexsAVisitar.size() < boolVertexsVisitats.size() && indexVertexsAVisitar.back() != boolVertexsVisitats.size() - 1) {
		// Per a cada següent possible visita
		for (int i = 0; i < boolVertexsVisitats.size(); i++) { 
			// Si el node a visitar no ha estat visitat
			if (boolVertexsVisitats[i] == false) { 
				*distanciaActual += distance_matrix[index_actual][i];
				SalesmanTrackBacktrackingGreedyRecursiu(distance_matrix, indexVertexsOptims, i, indexVertexsAVisitar, distanciaOptima, distanciaActual, boolVertexsVisitats);
			}
		}
	}
	else {
		// Si la distancia actual és millor que la distància optima, llavors ...
		if (*distanciaActual < *distanciaOptima) { 
			*distanciaOptima = *distanciaOptima;
			indexVertexsOptims = indexVertexsAVisitar;
		}
	}

	// Pas enrere :
	int index_a_eliminar = indexVertexsAVisitar.back();
	boolVertexsVisitats[indexVertexsAVisitar.back()] = false;	// Marquem com a no visitat el ultim node del camí d'index
	if (indexVertexsAVisitar.size() > 1) {
		*distanciaActual -= distance_matrix[indexVertexsAVisitar.end()[-1]][indexVertexsAVisitar.end()[-2]];	// Restem la distancia del ultim node
	}
	else { *distanciaActual = 0; }
	indexVertexsAVisitar.pop_back();						// Eliminiem l'ultium node de la llista d'index a visitar


}

CTrack SalesmanTrackBacktrackingGreedy(CGraph& graph, CVisits& visits)
{
	// Definim vector distàncies i camins
	vector<vector<double>> distance_matrix;	
	vector<vector<CTrack*>> track_matrix;

	// Fem resize amb NxN on N=nº de nodes a visitar
	distance_matrix.resize(visits.GetNVertices(), vector<double>(visits.GetNVertices()));
	track_matrix.resize(visits.GetNVertices(), vector<CTrack*>(visits.GetNVertices()));

	// Inicialitzacio matrius distance_matrix i track_matrix amb els valors corresponents
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

	// Definim variables de control de l'algorisme recursiu
	vector<int> indexVertexsAVisitar; // No podria ser CVisits?
	vector<int> indexVertexsOptims; // No podria ser CVisits?
	vector<bool> boolVertexsVisitats(visits.GetNVertices(), false); // No es pot reutilitzar variable dins del CVertex?
	int index_vertex_actual = 0;
	double distanciaOptima = numeric_limits<double>::max();
	double distanciaActual = 0;

	// Obtenim el cami d'index per recorrer les visites
	SalesmanTrackBacktrackingGreedyRecursiu(distance_matrix, indexVertexsOptims, index_vertex_actual, indexVertexsAVisitar, &distanciaOptima, &distanciaActual, boolVertexsVisitats);

	// Definim camí buit
	CTrack track(&graph);

	// Pas d'index a camins
	int last_index = 0;
	for (int index : indexVertexsOptims) {
		track.Append(*track_matrix[index][last_index]);
		last_index = index;
	}

	return CTrack(&graph);
}
