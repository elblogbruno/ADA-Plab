#include "pch.h"
#include "Graph.h"
#include "GraphApplicationDlg.h"
#include <set>



// =============================================================================
// CONVEX HULL =================================================================
// =============================================================================

// left ========================================================================
// Recta de p1 a p2. i posició del punt p respecte la recta
// resultat>0: p a la esquerra.
// resultat==0: p sobre la recta.
// resultat<0: p a la dreta

double PosicioRespeteRecta(CGPoint& a, CGPoint& b, CGPoint &c)
{
	return (a.m_Y - b.m_Y) * (c.m_X - b.m_X) - (a.m_X - b.m_X) * (c.m_Y - b.m_Y);
}

// AreaTriangle ================================================================

double AreaTriangle(CGPoint& a, CGPoint& b, CGPoint c)
{
	return abs((a.m_Y - b.m_Y) * (c.m_X - b.m_X) - (a.m_X - b.m_X) * (c.m_Y - b.m_Y)) / 2.0;
}


// QuickHull ===================================================================

CConvexHull QuickHull(CGraph& graph)
{
	return CConvexHull(&graph);
}