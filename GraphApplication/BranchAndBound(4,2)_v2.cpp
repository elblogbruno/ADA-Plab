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

void initMinMaxMatrix(vector<double>& min_cami, vector<double>& max_cami, const vector<vector<double>>& distance_matrix) {
	int totalVisites = distance_matrix[0].size();
	// Inicialitzem les matrius de camins amb distància = número de visites
	min_cami.resize(totalVisites);
	max_cami.resize(totalVisites);

	// Càlcul pel node inicial
	double maxim_cami = 0.0;
	double minim_cami = numeric_limits<double>::max();
	for (int i = 0; i < totalVisites - 1; i++) {
		if (distance_matrix[0][i] > maxim_cami)
			maxim_cami = distance_matrix[0][i];
		if (distance_matrix[0][i] < minim_cami && distance_matrix[0][i] != 0)
			minim_cami = distance_matrix[0][i];
	}
	min_cami[0] = minim_cami;
	max_cami[0] = maxim_cami;

	// Càlcul pels nodes intermitjos
	for (int i = 1; i < totalVisites - 1; i++) {
		maxim_cami = 0.0;
		minim_cami = numeric_limits<double>::max();
		for (int j = 0; j < totalVisites - 1; j++) {
			if (distance_matrix[i][j] > maxim_cami)
				maxim_cami = distance_matrix[i][j];
			if (distance_matrix[i][j] < minim_cami && distance_matrix[i][j] != 0)
				minim_cami = distance_matrix[i][j];
		}
		min_cami[i] = minim_cami;
		max_cami[i] = maxim_cami;
	}

	// Càlcul per l'últim node
	maxim_cami = 0.0;
	minim_cami = numeric_limits<double>::max();
	int ultim_node = totalVisites - 1;
	for (int i = 1; i < totalVisites - 2; i++) {
		if (distance_matrix[ultim_node][i] > maxim_cami)
			maxim_cami = distance_matrix[ultim_node][i];
		if (distance_matrix[ultim_node][i] < minim_cami && distance_matrix[ultim_node][i] != 0)
			minim_cami = distance_matrix[ultim_node][i];
	}
	min_cami[ultim_node] = minim_cami;
	max_cami[ultim_node] = maxim_cami;
}


double getMaxInitialWeight(const vector<vector<double>>& distance_matrix) {
	double max_weight = 0.0;
	double distance;
	for (int i = 1; i < distance_matrix[0].size(); i++) {
		distance = 0.0;
		for (int j = 0; j < distance_matrix[0].size(); j++) {
			if (distance_matrix[i][j] > distance) {
				distance = distance_matrix[i][j];
			}
		}
		max_weight += distance;
	}
	return max_weight;
}


// CBBNode ===============================================================

class CBBNode {
public:
	double m_Length;
	double m_WeigthMin; // Cota inferior
	double m_WeigthMax; // Cota superior
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
	// B&B1
	CBBNode(int indexNode, const int indexPare, vector<int> m_IndexVisites)
		: m_indexNode(indexNode)
		, m_Length(0)
	{
		m_VectorIndexVisites = m_IndexVisites;
		m_NumVisitesFetes = 1;
	}
	CBBNode(const CBBNode& node_pare, double distance, int indexNode, int indexArrayDeVisites)
		: m_indexNode(indexNode)
		, m_VectorIndexVisites(node_pare.m_VectorIndexVisites)
	{
		m_Length = node_pare.m_Length + distance;
		m_NumVisitesFetes = node_pare.m_NumVisitesFetes + 1;

		/*
		Exemple iter_swap:
			[] Indica node actual i
			// Últim node -> S'obté NumNodesVisitats - 1

			0 | /[1]/ | 2 | 3 -> No hi ha IterSwap
			0 | /1/ | [2] | 3 -> Llavors si hi ha IterSwap
		*/
		iter_swap(m_VectorIndexVisites.begin() + m_NumVisitesFetes - 1, m_VectorIndexVisites.begin() + indexArrayDeVisites);
	}
	// B&B2
	CBBNode(int indexNode, const int indexPare, vector<int> m_IndexVisites, double lenght, const vector<vector<double>>& distance_matrix, double totalVisites)
		: m_indexNode(indexNode)
	{
		m_VectorIndexVisites = m_IndexVisites;
		m_Length = lenght + distance_matrix[indexPare][indexNode];
		m_NumVisitesFetes = 1;

		// Calculem cota mínima i màxima per a tots els nodes no visitats
		for (int index = m_NumVisitesFetes; index < totalVisites; index++) {
			double minim_cami = numeric_limits<double>::max();
			double maxim_cami = 0.0;
			double distancia = numeric_limits<double>::max();

			// Si es el últim node
			if (index == totalVisites - 1) {
				// Si es l'últim node, no es calcula amb el primer perque mai (o casi mai) passarà
				for (int index_cami = 1; index_cami < totalVisites - 1; index_cami++) {
					int index_origen = m_VectorIndexVisites[index_cami];
					int index_desti = m_VectorIndexVisites[index];
					distancia = distance_matrix[index_origen][index_desti];

					if (distancia < minim_cami && distancia != 0)
						minim_cami = distancia;
					if (distancia > maxim_cami)
						maxim_cami = distancia;
				}
			}
			else {
				// Si no es l'últim node, es calcula totes les distancies menys amb la distancia final
				// No cal controlar que no es sumi a si mateix perquè val 0
				// for (int index_cami = 0; index_cami < totalVisites - 1; index_cami++) {
				for (int index_cami = 0; index_cami < totalVisites - 1; index_cami++) {
					int index_origen = m_VectorIndexVisites[index_cami];
					int index_desti = m_VectorIndexVisites[index];
					distancia = distance_matrix[index_origen][index_desti];

					if (distancia < minim_cami && distancia != 0)
						minim_cami = distancia;
					if (distancia > maxim_cami)
						maxim_cami = distancia;
				}
			}
			m_WeigthMin += minim_cami;
			m_WeigthMax += maxim_cami;
		}
	}

	CBBNode(const CBBNode& node_pare, vector<vector<double>> distance_matrix, int indexNode, int indexArrayDeVisites, int totalVisites)
		: m_indexNode(indexNode)
		, m_VectorIndexVisites(node_pare.m_VectorIndexVisites)
		, m_WeigthMin(0.0)
		, m_WeigthMax(0.0)
	{
		m_Length = node_pare.m_Length + distance_matrix[node_pare.m_indexNode][indexNode];
		m_NumVisitesFetes = node_pare.m_NumVisitesFetes + 1;
		iter_swap(m_VectorIndexVisites.begin() + m_NumVisitesFetes - 1, m_VectorIndexVisites.begin() + indexArrayDeVisites);

		// Càlcul camí màxim i mínim
		double maxim_cami = 0.0;
		double minim_cami = numeric_limits<double>::max();
		if (indexNode == totalVisites - 1) {		// Si és l'últim node
			for (int i = 1; i < totalVisites - 2; i++) {
				if (distance_matrix[indexNode][i] > maxim_cami)
					maxim_cami = distance_matrix[indexNode][i];
				if (distance_matrix[indexNode][i] < minim_cami)
					minim_cami = distance_matrix[indexNode][i];
			}
		}
		else {
			for (int i = 0; i < totalVisites - 1; i++) {
				if (distance_matrix[indexNode][i] > maxim_cami)
					maxim_cami = distance_matrix[indexNode][i];
				if (distance_matrix[indexNode][i] < minim_cami && distance_matrix[indexNode][i] != 0)
					minim_cami = distance_matrix[indexNode][i];
			}
		}
		m_WeigthMax = node_pare.m_WeigthMax - maxim_cami + distance_matrix[indexNode][node_pare.m_indexNode];
		m_WeigthMin = node_pare.m_WeigthMin - minim_cami + distance_matrix[indexNode][node_pare.m_indexNode];
	}

	CBBNode(const CBBNode& node_pare, double distance, int indexNode, int indexArrayDeVisites, int totalVisites, const vector<double>& min_cami, const vector<double>& max_cami)
		: m_indexNode(indexNode)
		, m_VectorIndexVisites(node_pare.m_VectorIndexVisites)
		, m_WeigthMin(0.0)
		, m_WeigthMax(0.0)
	{
		m_Length = node_pare.m_Length + distance;
		m_NumVisitesFetes = node_pare.m_NumVisitesFetes + 1;
		iter_swap(m_VectorIndexVisites.begin() + m_NumVisitesFetes - 1, m_VectorIndexVisites.begin() + indexArrayDeVisites);

		
		// Càlcul cotes mínimes i màximes
		m_WeigthMax = node_pare.m_WeigthMax - max_cami[indexNode] + distance;
		m_WeigthMin = node_pare.m_WeigthMin - min_cami[indexNode] + distance;
	}
};

// comparator ==================================================================

// Comparador per distància
// B&B 1
struct comparator1 {
	bool operator()(const CBBNode* s1, const CBBNode* s2) {
		return s1->m_Length > s2->m_Length;
	}
};

// Comparador per cotes
// B&B 2
struct comparator2 {
	bool operator()(const CBBNode* s1, const CBBNode* s2) {
		// return (s1->m_WeigthMin + s1->m_Length) > (s2->m_WeigthMin + s2->m_Length);
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
	priority_queue<CBBNode*, std::vector<CBBNode*>, comparator1> queue;

	// Definim node inicial o arrel
	CBBNode* node_inicial = new CBBNode(0, 0, index_visits);

	// Afegim node inicial a la cua
	queue.push(node_inicial);

	// Definim punter per recorrer i expandir l'arbre
	CBBNode* node_actual = new CBBNode();

	// Definim node optim
	CBBNode* best_node = new CBBNode;
	best_node->m_Length = numeric_limits<double>::max();

	// Definim variable amb el número de visites
	int numVisites = visits.GetNVertices();


	while (!queue.empty()) {
		node_actual = queue.top();	// Seleccionem el node més prometedor
		queue.pop();				// Borrem últim element

		// Per a cada possible fill del node, els afegim a la cua
		for (int i = node_actual->m_NumVisitesFetes; i < numVisites; i++) {
			double distance = distance_matrix[node_actual->m_indexNode][node_actual->m_VectorIndexVisites[i]];
			CBBNode* node_fill = new CBBNode(*node_actual, distance, node_actual->m_VectorIndexVisites[i], i);

			if (node_fill->m_Length < best_node->m_Length) {
				queue.push(node_fill);

				// Si és solució completa
				if (node_fill->m_NumVisitesFetes == numVisites) {
					// Si és millor que la solució actual
					// if(node_fill->m_Length < best_node->m_Length && node_fill->m_VectorIndexVisites.back() == numVisites - 1) -> Es mes lent
					if (node_fill->m_Length < best_node->m_Length && node_fill->m_VectorIndexVisites[numVisites - 1] == numVisites - 1)
						best_node = node_fill;
				}
			}
		}
	}

	// Definim camí buit
	CTrack track(&graph);

	// Pas d'index a camins
	int last_index = 0;
	for (int index : best_node->m_VectorIndexVisites) {
		CTrack* aux_track = track_matrix[index][last_index];
		if (aux_track != NULL)
			track.Append(*aux_track);
		last_index = index;
	}

	return track;
}



// SalesmanTrackBranchAndBound2 ===================================================

/* Seleccionar camí mque minimitzi la longitud del camí + cota mínima fàcil */
CTrack SalesmanTrackBranchAndBound2(CGraph& graph, CVisits &visits)
{	
	// Definim numero total de visites
	int numVisites = visits.GetNVertices();

	
	// Si el graf té més de 17 visites no el tractem
	if (numVisites >= 17) {
		CTrack track(&graph);
		return track;
	}
	
	// Si només hi han dues visites
	if (numVisites == 2) {
		// Definim camí buit
		CTrack track(&graph);

		// Definim vector distàncies i camins
		vector<vector<double>> distance_matrix;
		vector<vector<CTrack*>> track_matrix;
		initDistanceAndTrackMatrix(graph, visits, distance_matrix, track_matrix);

		// Inicialitzem array de visitas amb seqüència del 0 al n, on n són el número de visites
		vector<int> index_visits{ 0, 1 };
	
		// Pas d'index a camins
		int last_index = 0;
		for (int index : index_visits) {
			CTrack* aux_track = track_matrix[index][last_index];
			if (aux_track != NULL)
				track.Append(*aux_track);
			last_index = index;
		}

		return track;
	}

	// Definim vector distàncies i camins
	vector<vector<double>> distance_matrix;
	vector<vector<CTrack*>> track_matrix;
	initDistanceAndTrackMatrix(graph, visits, distance_matrix, track_matrix);

	vector<double> min_cami;
	vector<double> max_cami;
	initMinMaxMatrix(min_cami, max_cami, distance_matrix);

	// Inicialitzem array de visitas amb seqüència del 0 al n, on n són el número de visites
	vector<int> index_visits;
	index_visits.resize(visits.GetNVertices());
	iota(begin(index_visits), end(index_visits), 0);

	// Definim cua de prioritats
	priority_queue<CBBNode*, std::vector<CBBNode*>, comparator2> queue;

	// Definim node inicial o arrel
	CBBNode node_inicial(0, 0, index_visits, 0, distance_matrix, numVisites);

	// Test
	double distance = getMaxInitialWeight(distance_matrix);
	node_inicial.m_WeigthMax = distance;

	// Afegim node inicial a la cua
	queue.push(&node_inicial);

	// Definim punter per recorrer i expandir l'arbre
	CBBNode* node_actual = new CBBNode();

	// Definim node optim
	CBBNode* best_node = new CBBNode;
	best_node->m_Length = numeric_limits<double>::max();
	best_node->m_WeigthMin = numeric_limits<double>::max();

	// Definim Cota superior global
	double WeigthMaxGlobal = node_inicial.m_WeigthMax;


	while (!queue.empty()) {
		node_actual = queue.top();	// Seleccionem el node més prometedor
		queue.pop();				// Borrem últim element


		// Per a cada possible fill del node, els afegim a la cua
		for (int i = node_actual->m_NumVisitesFetes; i < node_actual->m_VectorIndexVisites.size(); i++) {
			// CBBNode* node_fill = new CBBNode(*node_actual, distance_matrix, node_actual->m_VectorIndexVisites[i], i, numVisites);
			double distance = distance_matrix[node_actual->m_indexNode][node_actual->m_VectorIndexVisites[i]];
			CBBNode* node_fill = new CBBNode(*node_actual, distance, node_actual->m_VectorIndexVisites[i], i, numVisites, min_cami, max_cami);
				
			// Només explorem el node si aquest té una cota mínima menor que la cota màxima global
			if (node_fill->m_WeigthMin <= WeigthMaxGlobal) {

				// Actualitzem Cota Superior Global en cas que sigui menor que la actual
				if (node_fill->m_WeigthMax < WeigthMaxGlobal)
					WeigthMaxGlobal = node_fill->m_WeigthMax;


				/*
				// Si és sol·lució final les dues cotes són iguals i tots els nodes són visitats
				if (node_fill->m_WeigthMax == node_fill->m_WeigthMin && node_fill->m_NumVisitesFetes == numVisites) {
					best_node = node_fill;
					// Declarem llista buida
					priority_queue<CBBNode*, std::vector<CBBNode*>, comparator2> queue_empty;
					// Marquem la llista de prioritat com a buida
					swap(queue, queue_empty);
					break;
				}
				*/
				queue.push(node_fill);

				// Si és solució completa
				if (node_fill->m_NumVisitesFetes == numVisites) {
					// Si és la millor solució
					// if (node_fill->m_Length < best_node->m_Length && node_fill->m_VectorIndexVisites.back() == numVisites - 1) 
					if (node_fill->m_Length < best_node->m_Length && node_fill->m_VectorIndexVisites[numVisites - 1] == numVisites - 1)
						best_node = node_fill;
				}					
			}
		}	
	}

	// Definim camí buit
	CTrack track(&graph);

	// Pas d'index a camins
	int last_index = 0;
	for(int index : best_node->m_VectorIndexVisites) {
		CTrack* aux_track = track_matrix[index][last_index];
		if (aux_track != NULL)
			track.Append(*aux_track);
		last_index = index;
	}

	return track;
}

// SalesmanTrackBranchAndBound3 ===================================================


CTrack SalesmanTrackBranchAndBound3(CGraph& graph, CVisits &visits)
{
	if (visits.GetNVertices() > 16) {
		CTrack track(&graph);
		return track;
	}

	// Definim vector distàncies i camins
	vector<vector<double>> distance_matrix;
	vector<vector<CTrack*>> track_matrix;
	initDistanceAndTrackMatrix(graph, visits, distance_matrix, track_matrix);

	vector<vector<double>> min_cami;
	vector<vector<double>> max_cami;

	// Inicialitzem array de visitas amb seqüència del 0 al n, on n són el número de visites
	vector<int> index_visits;
	index_visits.resize(visits.GetNVertices());
	iota(begin(index_visits), end(index_visits), 0);

	// Definim cua de prioritats
	priority_queue<CBBNode*, std::vector<CBBNode*>, comparator2> queue;

	// Definim numero total de visites
	int numVisites = visits.GetNVertices();

	// Definim node inicial o arrel
	CBBNode node_inicial(0, 0, index_visits, 0, distance_matrix, numVisites);

	// Test
	double distance = getMaxInitialWeight(distance_matrix);
	node_inicial.m_WeigthMax = distance;

	// Afegim node inicial a la cua
	queue.push(&node_inicial);

	// Definim punter per recorrer i expandir l'arbre
	CBBNode* node_actual = new CBBNode();

	// Definim node optim
	CBBNode* best_node = new CBBNode;
	best_node->m_Length = numeric_limits<double>::max();
	best_node->m_WeigthMin = numeric_limits<double>::max();

	// Definim Cota superior global
	double WeigthMaxGlobal = node_inicial.m_WeigthMax;


	while (!queue.empty()) {
		node_actual = queue.top();	// Seleccionem el node més prometedor
		queue.pop();				// Borrem últim element

		// Només seguim expandint si el node actual pot ser millor que el millor node
		// if (node_actual->m_Length + node_actual->m_WeigthMin < WeigthMaxGlobal) {
		if (node_actual->m_WeigthMin <= WeigthMaxGlobal) {

			// Per a cada possible fill del node, els afegim a la cua
			for (int i = node_actual->m_NumVisitesFetes; i < node_actual->m_VectorIndexVisites.size(); i++) {
				CBBNode* node_fill = new CBBNode(*node_actual, distance_matrix, node_actual->m_VectorIndexVisites[i], i, numVisites);

				// Actualitzem Cota Superior Global en cas que sigui menor que la actual
				if (node_fill->m_WeigthMax < WeigthMaxGlobal)
					WeigthMaxGlobal = node_fill->m_WeigthMax;

				// Només explorem el node si aquest té una cota mínima menor que la cota màxima global
				if (node_fill->m_WeigthMin <= WeigthMaxGlobal) {

					/*
					// Si és sol·lució final les dues cotes són iguals i tots els nodes són visitats
					if (node_fill->m_WeigthMax == node_fill->m_WeigthMin && node_fill->m_NumVisitesFetes == numVisites) {
						best_node = node_fill;
						// Declarem llista buida
						priority_queue<CBBNode*, std::vector<CBBNode*>, comparator2> queue_empty;
						// Marquem la llista de prioritat com a buida
						swap(queue, queue_empty);
						break;
					}
					*/
					queue.push(node_fill);

					if (node_fill->m_NumVisitesFetes == numVisites && node_fill->m_Length < best_node->m_Length && node_fill->m_VectorIndexVisites[numVisites - 1] == numVisites - 1) {
						best_node = node_fill;
					}
				}
			}
		}
	}

	// Definim camí buit
	CTrack track(&graph);

	// Pas d'index a camins
	int last_index = 0;
	for (int index : best_node->m_VectorIndexVisites) {
		CTrack* aux_track = track_matrix[index][last_index];
		if (aux_track != NULL)
			track.Append(*aux_track);
		last_index = index;
	}

	return track;
}
