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


CTrack SalesmanTrackBacktrackingGreedy(CGraph& graph, CVisits& visits)
{
	return CTrack(&graph);
}
