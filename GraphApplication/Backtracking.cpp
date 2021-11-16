#include "pch.h"
#include "Graph.h"
#include <set>
#include <algorithm>


// =============================================================================
// SalesmanTrackBacktracking ===================================================
// =============================================================================

/* Un cami correcte significa que totes les arestes han estat visitades */
bool cami_correcte(CVisits& visits)
{
	for (CVertex* v : visits.m_Vertices)
	{
		if (v != visits.m_Vertices.back())
		{
			bool correcte = false;
			for (CEdge* pE : v->m_Edges)
			{
				if (pE->m_BackTrackingVisit)
				{
					correcte = true;
					break;
				}
			}
			if (!correcte)
				return false;
		}

	}
	return true;

}

void BacktrackingRecursiu(CVisits& visits, CVertex* pActual, vector<CVertex*>& finalTrack, vector<CVertex*>& actualTrack, double& bestDistance, double& actualDistance, CVertex* pDesti) {

	// Si tots han estat visitats i la sol.lucio actual es millor que la anterior, es guarda al cami optim en cas que sigui millor
	if (pActual == pDesti) {
		if (bestDistance > actualDistance) {
			if (cami_correcte(visits)) //Un cami correcte significa que totes les arestes han estat visitades 
			{
				//actualitzem millor solucio
				bestDistance = actualDistance;
				finalTrack = actualTrack;
			}
		}
	}
	else {
		for (CEdge* aresta_actual : pActual->m_Edges) { // Per a cada aresta del node actual
			CVertex* vertex_vei = aresta_actual->m_pDestination;

			if (aresta_actual->m_BackTrackingVisit == false && bestDistance > actualDistance + aresta_actual->m_Length) { // Si no he visitat la aresta sortint tambe ens interesa podar, ja que aquella aresta ens pot portar a un estat pitjor 
				// Pas endavant
				actualTrack.push_back(vertex_vei);
				actualDistance += aresta_actual->m_Length;
				aresta_actual->m_BackTrackingVisit = true;

				BacktrackingRecursiu(visits, vertex_vei, finalTrack, actualTrack, bestDistance, actualDistance, pDesti);

				// Pas enrere
				actualDistance -= aresta_actual->m_Length;
				actualTrack.pop_back();
				aresta_actual->m_BackTrackingVisit = false;
			}
		}
	}
}

CTrack SalesmanTrackBacktracking(CGraph& graph, CVisits& visits)
{
	// Inicialitzem el cami optim com el mes llarg i buit
	vector<CVertex*> bestTrack;
	bestTrack.push_back(visits.m_Vertices.front());
	double bestDistance = numeric_limits<double>::max();

	// Inicialitzem el cami actual com el mes curt
	vector<CVertex*> actualTrack;
	actualTrack.push_back(visits.m_Vertices.front());
	double actualDistance = 0;

	// Marquem tots els vertexs del graf com a no marcats:
	/* No cal, ja estan inicialitzats de per si
	for (CVertex vertex : graph.m_Vertices) {
		vertex.m_BackTrackingVisit = false;
	}
	*/
	visits.m_Vertices.front()->m_BackTrackingVisit = true; // Marquem el primer coma  visitat

	BacktrackingRecursiu(visits, visits.m_Vertices.front(), bestTrack, actualTrack, bestDistance, actualDistance, visits.m_Vertices.back());

	//bestTrack.push_back(visits.m_Vertices.back());

	CTrack finalTrack(&graph);

	while (bestTrack.size() >= 2) {
		CVertex* vertex_actual = bestTrack[0];

		for (CEdge* edge : vertex_actual->m_Edges) {		// Per a cada aresta del node actual
			if (edge->m_pDestination == bestTrack[1]) {		// Busquem aquella que porti al següent node
				finalTrack.AddLast(edge);					// Una vegada trobada l'afegim al cami CTrack
				bestTrack.erase(bestTrack.begin());			// Eliminem el vertex actual de la llista
				break;
			}
		}
	}


	return finalTrack;
}
// =============================================================================
// SalesmanTrackBacktrackingGreedy =============================================
// =============================================================================

bool totsVisitats(vector<bool>& boolVertexsVisitats) {
	for (bool i : boolVertexsVisitats) { if (i == false) return false; }
	return true;
}

void SalesmanTrackBacktrackingGreedyRecursiu(vector<vector<double>>& distance_matrix, vector<int>& indexVertexsOptims, int index_actual, vector<int>& indexVertexsAVisitar, double* distanciaOptima, double* distanciaActual, vector<bool>& boolVertexsVisitats) {
	// distance_matrix = Info taulel de distancies
	// indexVertexsOptims = Llista d'indexs que formen el cami optim
	// index_actual = Posicio actual
	// indexVertexsAVisitar = Llista dels index que s'han de visitar
	
	indexVertexsAVisitar.push_back(index_actual);		// Afegim al cami el node a visitar
	boolVertexsVisitats[index_actual] = true;			// El marquem com a visitat

	// Si és sol.lució completa, llavors:
	if (totsVisitats(boolVertexsVisitats) && indexVertexsAVisitar.back() == boolVertexsVisitats.size() - 1) {
	// if (indexVertexsAVisitar.size() == boolVertexsVisitats.size() && indexVertexsAVisitar.back() == boolVertexsVisitats.size() - 1) {
		// Si la distancia actual és millor que la distància optima, llavors ...
		if (*distanciaActual < *distanciaOptima) {
			*distanciaOptima = *distanciaActual;
			indexVertexsOptims = indexVertexsAVisitar;
		}
	}
	else {
		// Per a cada següent possible visita
		for (int i = 1; i < boolVertexsVisitats.size(); i++) {
			// Si el node a visitar no ha estat visitat
			if (boolVertexsVisitats[i] == false) {
				*distanciaActual += distance_matrix[index_actual][i];
				SalesmanTrackBacktrackingGreedyRecursiu(distance_matrix, indexVertexsOptims, i, indexVertexsAVisitar, distanciaOptima, distanciaActual, boolVertexsVisitats);
			}
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

/*
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
*/
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
		col = 0;
		// Cridem Dijkstra per a cada node del Graph
		DijkstraQueue(graph, vertex);
		for (CVertex* vertex_2 : visits.m_Vertices) {
			CTrack* aux = new CTrack(&graph);
			CVertex* actV = vertex_2;
			while (actV != vertex) {
				aux->AddFirst(actV->m_DijkstraAnterior);
				//aux->AddFirst(actV->m_DijkstraAnterior->m_pReverseEdge);
				actV = actV->m_DijkstraAnterior->m_pOrigin;
				//actV = actV->m_DijkstraAnterior->m_pReverseEdge->m_pDestination;
			}
			if (vertex != vertex_2) {
				// track_matrix[row][col] = aux;
				// distance_matrix[row][col] = aux->Length();
				track_matrix[col][row] = aux;
				distance_matrix[col][row] = aux->Length();
			}
			col++;
		}
		row++;
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
		CTrack* aux_track = track_matrix[index][last_index];
		if (aux_track != NULL)
			track.Append(*aux_track);
		last_index = index;
	}

	return track;
}
