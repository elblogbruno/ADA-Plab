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


CTrack SalesmanTrackBacktrackingGreedy(CGraph& graph, CVisits& visits)
{
	return CTrack(&graph);
}
