#include "pch.h"
#include "Graph.h"
#include <queue>
#include <iostream>
#include <iomanip> 

#include <numeric>

void initDistanceAndTrackMatrix(CGraph &graph, CVisits& visits, vector<vector<double>>& distance_matrix, vector<vector<CTrack*>>& track_matrix) {
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
				actV = actV->m_DijkstraAnterior->m_pOrigin;
			}
			if (vertex != vertex_2) {
				track_matrix[col][row] = aux;
				distance_matrix[col][row] = aux->Length();
			}
			col++;
		}
		row++;
	}
}

// CBBNode ===============================================================

class CBBNode {
public:
	double m_Length;
	double m_WeigthMin; // Cota inferior. peso del nodo a más pesado más largo es su posible camino
	int m_NumVisitesFetes;
	vector<int> m_VectorIndexVisites;	// Guardem index de les visites per accedir a la matriu
	int m_indexNode;

	/*
	Exemple :
	t = 0
		int m_VisitesFetes = 3
		vector<int> m_IndexVisites -> 0 | 2 | 5 | 1 | 3 | 4 | 6
			Deduim que les visites fetes són : 0 | 2 | 5
			I les restants són : 1 | 3 | 4 | 6

	t = 1
		int m_VisitesFetes = 4
		vector<int> m_IndexVisites -> 0 | 2 | 5 | 1 | 3 | 4 | 6
			Deduim que les visites fetes són : 0 | 2 | 5 | 1
			I les restants són : 3 | 4 | 6
		
	*/


	// Pointer al pare? -> Bruno diu que es B&B V3

public:
	CBBNode() {
		m_Length = 0;

	}
	CBBNode(int indexNode, const int indexPare, vector<int> m_IndexVisites, double lenght, const vector<vector<double>>& distance_matrix)
		: m_indexNode(indexNode)
	{
		m_VectorIndexVisites = m_IndexVisites;
		m_Length = lenght + distance_matrix[indexPare][indexNode];
		m_NumVisitesFetes = 1;
	}
	CBBNode(const CBBNode& node_pare, vector<vector<double>> distance_matrix, int indexNode, int indexArrayDeVisites)
		: m_indexNode(indexNode)
		, m_VectorIndexVisites(node_pare.m_VectorIndexVisites)
	{
		m_Length = node_pare.m_Length + distance_matrix[node_pare.m_indexNode][indexNode];
		m_NumVisitesFetes = node_pare.m_NumVisitesFetes + 1;

		/*
		Exemple iter_swap:
			[] Indica node actual i
			// Últim node -> S'obté NumNodesVisitats - 1

			0 | /[1]/ | 2 | 3 -> No hi ha IterSwap
			0 | /1/ | [2] | 3 -> Llavors si hi ha IterSwap
		*/
		iter_swap(m_VectorIndexVisites.begin() + m_NumVisitesFetes - 1, m_VectorIndexVisites.begin() + indexArrayDeVisites );
	}
};

// comparator ==================================================================

struct comparator {
	bool operator()(const CBBNode* s1, const CBBNode* s2) {
		return s1->m_WeigthMin > s2->m_WeigthMin;
	}
};

// SalesmanTrackBranchAndBound1 ===================================================

/* Completar el camí més curt */
CTrack SalesmanTrackBranchAndBound1(CGraph& graph, CVisits& visits)
{
	// Definim vector distàncies i camins
	vector<vector<double>> distance_matrix;
	vector<vector<CTrack*>> track_matrix;
	initDistanceAndTrackMatrix(graph, visits, distance_matrix, track_matrix);

	// Inicialitzem array de visitas amb seqüència del 0 al n, on n són el número de visites
	vector<int> index_visits;
	index_visits.resize(visits.GetNVertices());
	iota(begin(index_visits), end(index_visits), 0);

	// Definim cua de prioritats
	priority_queue<CBBNode*, std::vector<CBBNode*>, comparator> queue;


	// Definim node inicial o arrel
	CBBNode node_inicial(0, 0, index_visits, 0, distance_matrix);

	// Afegim node inicial a la cua
	queue.push(&node_inicial);

	// Definim punter per recorrer i expandir l'arbre
	CBBNode* node_actual = new CBBNode();
	

	// Definim node optim
	CBBNode best_node;
	best_node.m_Length = numeric_limits<double>::max();

	
	while (!queue.empty()) {
		node_actual = queue.top(); // Seleccionem el node més prometedor
		queue.pop(); // Borrem últim element

		// Per a cada possible fill del node, els afegim a la cua
		for (int i = node_actual->m_NumVisitesFetes; i < node_actual->m_VectorIndexVisites.size(); i++) {
			CBBNode* node_fill = new CBBNode(*node_actual, distance_matrix, node_actual->m_VectorIndexVisites[i], i);
			queue.push(node_fill);

			// Si és solució completa
			if (node_fill->m_Length < best_node.m_Length && node_fill->m_NumVisitesFetes == node_fill->m_VectorIndexVisites.size() && node_fill->m_VectorIndexVisites.back() == node_fill->m_VectorIndexVisites.size() - 1) {
				best_node = *node_fill;
			}


		}
	}

	// Definim camí buit
	CTrack track(&graph);

	// Pas d'index a camins
	int last_index = 0;
	for (int index : best_node.m_VectorIndexVisites) {
		CTrack* aux_track = track_matrix[index][last_index];
		if (aux_track != NULL)
			track.Append(*aux_track);
		last_index = index;
	}

	return track;
}

// SalesmanTrackBranchAndBound2 ===================================================

CTrack SalesmanTrackBranchAndBound2(CGraph& graph, CVisits &visits)
{
	return CTrack(&graph);
}

// SalesmanTrackBranchAndBound3 ===================================================


CTrack SalesmanTrackBranchAndBound3(CGraph& graph, CVisits &visits)
{
	return CTrack(&graph);
}
