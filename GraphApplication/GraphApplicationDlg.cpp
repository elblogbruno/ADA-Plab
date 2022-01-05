
// GraphApplicationDlg.cpp: archivo de implementación
//

#include "pch.h"
#include "framework.h"
#include "GraphApplication.h"
#include "GraphApplicationDlg.h"
#include "CGraphDimensionsDlg.h"
#include "CVisitsDimensionsDlg.h"
#include "CGridGraphDlg.h"
#include "afxdialogex.h"
#include "Logs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// =============================================================================
// CGraphApplicationDlg ========================================================
// =============================================================================

CGraphApplicationDlg* pGraphApplicationDlg;

// Cuadro de diálogo de CGraphApplicationDlg

CGraphApplicationDlg::CGraphApplicationDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_GRAPHAPPLICATION_DIALOG, pParent)
	, m_Graph(false)
	, m_Visits(&m_Graph)
	, m_Track(&m_Graph)
	, m_Track2(&m_Graph)
	, m_SpanningTree(&m_Graph)
	, m_ConvexHull(&m_Graph)
{
	pGraphApplicationDlg = this;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraphApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAPH_VIEW, m_GraphCtrl);
	DDX_Control(pDX, IDC_CHECK_NEW_VERTICES, m_NewVerticesCtrl);
	DDX_Control(pDX, IDC_CHECK_EDIT_VERTICES, m_EditVerticesCtrl);
	DDX_Control(pDX, IDC_CHECK_MOVE_VERTICES, m_MoveVerticesCtrl);
	DDX_Control(pDX, IDC_CHECK_DELETE_VERTICES, m_DeleteVerticesCtrl);
	DDX_Control(pDX, IDC_CHECK_NEW_EDGES, m_NewEdgesCtrl);
	DDX_Control(pDX, IDC_CHECK_EDIT_EDGES, m_NewEditEdges);
	DDX_Control(pDX, IDC_CHECK_DELETE_EDGES, m_DeleteEdgesCtrl);
	DDX_Control(pDX, IDC_CHECK_PANNING, m_PanningCtrl);
	DDX_Control(pDX, IDC_CHECK_NEW_VISITS, m_NewVisitsCtrl);

	DDX_Control(pDX, IDC_BUTTON_BREAK, m_BreakCtrl);
	DDX_Control(pDX, IDC_BUTTON_CONTINUE, m_ContinueCtrl);
}

BEGIN_MESSAGE_MAP(CGraphApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD_GRAPH, &CGraphApplicationDlg::OnBnClickedButtonLoadGraph)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_GRAPH, &CGraphApplicationDlg::OnBnClickedButtonSaveGraph)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_GRAPH, &CGraphApplicationDlg::OnBnClickedButtonCleanGraph)
	ON_BN_CLICKED(IDC_CHECK_NEW_VERTICES, &CGraphApplicationDlg::OnBnClickedCheckNewVertices)
	ON_BN_CLICKED(IDC_CHECK_MOVE_VERTICES, &CGraphApplicationDlg::OnBnClickedCheckMoveVertices)
	ON_BN_CLICKED(IDC_CHECK_DELETE_VERTICES, &CGraphApplicationDlg::OnBnClickedCheckDeleteVertices)
	ON_BN_CLICKED(IDC_CHECK_NEW_EDGES, &CGraphApplicationDlg::OnBnClickedCheckNewEdges)
	ON_BN_CLICKED(IDC_CHECK_EDIT_EDGES, &CGraphApplicationDlg::OnBnClickedCheckEditEdges)
	ON_BN_CLICKED(IDC_CHECK_DELETE_EDGES, &CGraphApplicationDlg::OnBnClickedCheckDeleteEdges)
	ON_BN_CLICKED(IDC_CHECK_PANNING, &CGraphApplicationDlg::OnBnClickedCheckPanning)
	ON_BN_CLICKED(IDC_CHECK_EDIT_VERTICES, &CGraphApplicationDlg::OnBnClickedCheckEditVertices)
	ON_BN_CLICKED(IDC_CHECK_NEW_VISITS, &CGraphApplicationDlg::OnBnClickedCheckNewVisits)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_VISITS, &CGraphApplicationDlg::OnBnClickedButtonCleanVisits)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_VISITS, &CGraphApplicationDlg::OnBnClickedButtonLoadVisits)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_VISITS, &CGraphApplicationDlg::OnBnClickedButtonSaveVisits)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_TRACK, &CGraphApplicationDlg::OnBnClickedButtonLoadTrack)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TRACK, &CGraphApplicationDlg::OnBnClickedButtonSaveTrack)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_TRACK, &CGraphApplicationDlg::OnBnClickedButtonCleanTrack)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_SPANNING_TREE, &CGraphApplicationDlg::OnBnClickedButtonLoadSpanningTree)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SPANNING_TREE, &CGraphApplicationDlg::OnBnClickedButtonSaveSpanningTree)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_SPANNING_TREE, &CGraphApplicationDlg::OnBnClickedButtonCleanSpanningTree)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_RANDOM_GRAPH, &CGraphApplicationDlg::OnBnClickedButtonCreateRandomGraph)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_RANDOM_VISITS, &CGraphApplicationDlg::OnBnClickedButtonCreateRandomVisits)
	ON_BN_CLICKED(IDC_BUTTON_PRIM, &CGraphApplicationDlg::OnBnClickedButtonPrim)
	ON_BN_CLICKED(IDC_BUTTON_KRUSKAL, &CGraphApplicationDlg::OnBnClickedButtonKruskal)
	ON_BN_CLICKED(IDC_BUTTON_DIJKSTRA, &CGraphApplicationDlg::OnBnClickedButtonDijkstra)
	ON_BN_CLICKED(IDC_BUTTON__DIJKSTRA_QUEUE, &CGraphApplicationDlg::OnBnClickedButtonDijkstraQueue)
	/* Modificacio meva*/
	ON_BN_CLICKED(IDC_BUTTON_D_VERTEX, &CGraphApplicationDlg::OnBnClickedButtonDVertex)
	ON_BN_CLICKED(IDC_BUTTON_D_ARESTES, &CGraphApplicationDlg::OnBnClickedButtonDArestes)
	ON_BN_CLICKED(IDC_BUTTON_D_VISITES, &CGraphApplicationDlg::OnBnClickedButtonDVisites)
	/* -----------------*/
	ON_BN_CLICKED(IDC_BUTTON_GREEDY, &CGraphApplicationDlg::OnBnClickedButtonGreedy)
	ON_BN_CLICKED(IDC_BUTTON_BACKTRACKING, &CGraphApplicationDlg::OnBnClickedButtonBacktracking)
	ON_BN_CLICKED(IDC_BUTTON_BACKTRACKING_GREEDY, &CGraphApplicationDlg::OnBnClickedButtonBacktrackingGreedy)
	ON_BN_CLICKED(IDC_BUTTON_BRANCH_BOUND1, &CGraphApplicationDlg::OnBnClickedButtonBranchBound1)
	ON_BN_CLICKED(IDC_BUTTON_BRANCH_BOUND2, &CGraphApplicationDlg::OnBnClickedButtonBranchBound2)
	ON_BN_CLICKED(IDC_BUTTON_BRANCH_BOUND3, &CGraphApplicationDlg::OnBnClickedButtonBranchBound3)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_DISTANCES, &CGraphApplicationDlg::OnBnClickedButtonLoadDistances)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_DISTANCES, &CGraphApplicationDlg::OnBnClickedButtonSaveDistances)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_DISTANCES, &CGraphApplicationDlg::OnBnClickedButtonCleanDistances)
	ON_BN_CLICKED(IDC_BUTTON_TROBA_CAMI1, &CGraphApplicationDlg::OnBnClickedButtonTrobaCami1)
	ON_BN_CLICKED(IDC_BUTTON_TROBA_CAMI2, &CGraphApplicationDlg::OnBnClickedButtonTrobaCami2)
	ON_BN_CLICKED(IDC_BUTTON_TROBA_CAMI3, &CGraphApplicationDlg::OnBnClickedButtonTrobaCami3)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_CONVEX_HULL, &CGraphApplicationDlg::OnBnClickedButtonLoadConvexHull)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_CONVEX_HULL, &CGraphApplicationDlg::OnBnClickedButtonSaveConvexHull)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN_CONVEX_HULL, &CGraphApplicationDlg::OnBnClickedButtonCleanConvexHull)
	ON_BN_CLICKED(IDC_BUTTON_QUICK_HULL, &CGraphApplicationDlg::OnBnClickedButtonQuickHull)
	ON_BN_CLICKED(IDC_BUTTON_BREAK, &CGraphApplicationDlg::OnBnClickedButtonBreak)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, &CGraphApplicationDlg::OnBnClickedButtonContinue)
	ON_BN_CLICKED(IDC_BUTTON_TO_PLANNAR, &CGraphApplicationDlg::OnBnClickedButtonToPlannar)
	ON_BN_CLICKED(IDC_BUTTON_TROBA_CAMI_B_B1, &CGraphApplicationDlg::OnBnClickedButtonTrobaCamiBB1)
	ON_BN_CLICKED(IDC_BUTTON_TROBA_CAMI_B_B2, &CGraphApplicationDlg::OnBnClickedButtonTrobaCamiBB2)
	ON_BN_CLICKED(IDC_BUTTON_TROBA_CAMI_PROGRAMACIO_DINAMICA, &CGraphApplicationDlg::OnBnClickedButtonTrobaCamiProgramacioDinamica)
	ON_BN_CLICKED(IDC_BUTTON_TROBA_CAMI_PROGRAMACIO_DINAMICA_B_B, &CGraphApplicationDlg::OnBnClickedButtonTrobaCamiProgramacioDinamicaBB)
	ON_BN_CLICKED(IDC_BUTTON_TROBA_CAMI_B_B4, &CGraphApplicationDlg::OnBnClickedButtonTrobaCamiBB4)
	ON_BN_CLICKED(IDC_BUTTON_PROBABILISTIC, &CGraphApplicationDlg::OnBnClickedButtonProbabilistic)
	ON_BN_CLICKED(IDC_BUTTON_GRID_GRAPH, &CGraphApplicationDlg::OnBnClickedButtonGridGraph)
	ON_COMMAND(ID_VIEW_VIEWNAMES, &CGraphApplicationDlg::OnViewViewnames)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_VIEW_VIEWVERTICES, &CGraphApplicationDlg::OnViewViewvertices)
	ON_COMMAND(ID_VIEW_VIEWEDGES, &CGraphApplicationDlg::OnViewViewedges)
	ON_COMMAND(ID_VIEW_VIEWDISTANCES, &CGraphApplicationDlg::OnViewViewdistances)
	ON_COMMAND(ID_VIEW_VIEWVISITS, &CGraphApplicationDlg::OnViewViewvisits)
	ON_COMMAND(ID_VIEW_VIEWTRACK, &CGraphApplicationDlg::OnViewViewtrack)
	ON_COMMAND(ID_VIEW_VIEWSPANNINGTREE, &CGraphApplicationDlg::OnViewViewspanningtree)
	ON_COMMAND(ID_ANALISIS_GREEDY, &CGraphApplicationDlg::OnAnalisisGreedy)
	ON_COMMAND(ID_ANALISIS_BTPUR, &CGraphApplicationDlg::OnAnalisisBtpur)
	ON_COMMAND(ID_ANALISIS_BTGREEDY, &CGraphApplicationDlg::OnAnalisisBtgreedy)
	ON_COMMAND(ID_ANALISIS_BB1, &CGraphApplicationDlg::OnAnalisisBb1)
	ON_COMMAND(ID_ANALISIS_BB2, &CGraphApplicationDlg::OnAnalisisBb2)
	ON_COMMAND(ID_ANALISIS_BB3, &CGraphApplicationDlg::OnAnalisisBb3)
END_MESSAGE_MAP()


// Controladores de mensajes de CGraphApplicationDlg

BOOL CGraphApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_GraphCtrl.m_pGraph = &m_Graph;
	m_GraphCtrl.m_pVisits = &m_Visits;
	m_GraphCtrl.m_pTrack = &m_Track;
	m_GraphCtrl.m_pTrack2 = &m_Track2;
	m_GraphCtrl.m_pSpanningTree = &m_SpanningTree;
	m_GraphCtrl.m_pConvexHull = &m_ConvexHull;
	m_GraphCtrl.m_DisplayNames=true;
	m_GraphCtrl.m_DisplayDistances = false;
	m_GraphCtrl.m_DisplayVertices = true;
	m_GraphCtrl.m_DisplayEdges = true;
	m_GraphCtrl.m_DisplayVisits = true;
	m_GraphCtrl.m_DisplayTrack = true;
	m_GraphCtrl.m_DisplaySpanningTree = true;
	UpdateGrafDisplay();

	m_BreakCtrl.ShowWindow(SW_HIDE);
	m_ContinueCtrl.ShowWindow(SW_HIDE);

	OnBnClickedCheckPanning();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional
	cout << "ONINIT OK" << endl;
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CGraphApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CGraphApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CGraphApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// OnBnClickedButtonLoadGraph ==================================================

void CGraphApplicationDlg::OnBnClickedButtonLoadGraph()
{
	CFileDialog dlg(true, NULL, NULL, OFN_FILEMUSTEXIST,
		"Fichero de grafo (*.GR)|*.GR|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonLoadGraph %s", dlg.GetPathName());
		try {
			m_Visits.Clear();
			m_Track.Clear();
			m_Track2.Clear();
			m_SpanningTree.Clear();
			m_ConvexHull.Clear();
			m_Graph.Load(dlg.GetPathName());
			cout << "Graph   : " << dlg.GetPathName() << endl;
			cout << "Vertices: " << m_Graph.GetNVertices() << endl;
			cout << "Edges   : " << m_Graph.GetNEdges() << endl;
			m_GraphCtrl.m_DisplayDistances = false;
			PrintLog("OK");
		}
		catch (exception &ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
		m_GraphCtrl.Show();
	}
}

// OnBnClickedButtonSaveGraph =================================================

void CGraphApplicationDlg::OnBnClickedButtonSaveGraph()
{
	CFileDialog dlg(false, ".GR", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Fichero de grafo (*.GR)|*.GR|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonSaveGraph %s", dlg.GetPathName());
		try {
			m_Graph.Save(dlg.GetPathName());
			PrintLog("OK");
		}
		catch (exception &ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
	}
}

// OnBnClickedButtonCreateRandomGraph ==========================================

void CGraphApplicationDlg::OnBnClickedButtonCreateRandomGraph()
{
	CGraphDimensionsDlg dlg;
	dlg.m_Vertices = 10;
	dlg.m_Edges = 20;
	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonCreateRandomGraph %d vertices %d aristas", dlg.m_Vertices, dlg.m_Edges);
		try {
			m_Visits.Clear();
			m_Track.Clear();
			m_Track2.Clear();
			m_SpanningTree.Clear();
			m_ConvexHull.Clear();
			m_Graph.RandomCreation(dlg.m_Vertices, dlg.m_Edges);
			cout << "Grafo aleatorio: " << dlg.m_Vertices << " vertices " << dlg.m_Edges << " aristas" << endl;
			m_GraphCtrl.m_DisplayDistances = false;
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
		m_GraphCtrl.Show();
	}
}

// OnBnClickedButtonGridGraph ==================================================

void CGraphApplicationDlg::OnBnClickedButtonGridGraph()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	CGridGraphDlg dlg;
	dlg.m_RowsSz = 100;
	dlg.m_ColumnsSz = 100;

	if (dlg.DoModal() == IDOK) {
		try {
			m_Visits.Clear();
			m_Track.Clear();
			m_Track2.Clear();
			m_SpanningTree.Clear();
			m_ConvexHull.Clear();
			m_Graph.CreateGrid(dlg.m_RowsSz, dlg.m_ColumnsSz);
			cout << "Grafo cuadricula: " << m_Graph.GetNVertices() << " vertices " << m_Graph.GetNEdges() << " aristas" << endl;
			PrintLog("OnBnClickedButtonGridGraph %d rows %d columns", dlg.m_RowsSz, dlg.m_ColumnsSz);
			m_GraphCtrl.m_DisplayDistances = false;
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
		m_GraphCtrl.Show();
	}
}

// OnBnClickedButtonToPlannar ==================================================

void CGraphApplicationDlg::OnBnClickedButtonToPlannar()
{
	PrintLog("OnBnClickedButtonToPlannar");
	m_Visits.Clear();
	m_Track.Clear();
	m_Track2.Clear();
	m_SpanningTree.Clear();
	m_ConvexHull.Clear();
	cout << "To Plannar" << endl;
	m_Graph.ToPlannar();
	cout << "Vertices: " << m_Graph.GetNVertices() << endl;
	cout << "Edges   : " << m_Graph.GetNEdges() << endl;
	m_GraphCtrl.Invalidate();
}

// OnBnClickedButtonCleanGraph =================================================

void CGraphApplicationDlg::OnBnClickedButtonCleanGraph()
{
	PrintLog("OnBnClickedButtonCleanGraph");
	m_Visits.Clear();
	m_Track.Clear();
	m_Track2.Clear();
	m_SpanningTree.Clear();
	m_ConvexHull.Clear();
	m_Graph.Clear();
	m_GraphCtrl.Show();
}

// OnBnClickedButtonLoadDistances ==============================================

void CGraphApplicationDlg::OnBnClickedButtonLoadDistances()
{
	CFileDialog dlg(true, NULL, NULL, OFN_FILEMUSTEXIST,
		"Fichero de distancias (*.DIS)|*.DIS|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonLoadDistances %s",dlg.GetPathName());
		try {
			m_Visits.Clear();
			m_Track.Clear();
			m_Track2.Clear();
			m_SpanningTree.Clear();
			m_ConvexHull.Clear();
			m_Graph.LoadDistances(dlg.GetPathName());
			m_GraphCtrl.m_DisplayDistances = true;
			UpdateGrafDisplay();
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
	}
}

// OnBnClickedButtonSaveDistances ==============================================

void CGraphApplicationDlg::OnBnClickedButtonSaveDistances()
{
	CFileDialog dlg(false, ".DIS", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Fichero de distancias (*.DIS)|*.DIS|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonSaveDistances %s", dlg.GetPathName());
		try {
			m_Graph.SaveDistances(dlg.GetPathName());
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
	}
}

// OnBnClickedButtonCleanDistances =============================================

void CGraphApplicationDlg::OnBnClickedButtonCleanDistances()
{
	PrintLog("OnBnClickedButtonCleanDistances");
	m_Graph.ClearDistances();
	m_GraphCtrl.Invalidate();
}

// OnBnClickedCheckPanning =====================================================

void CGraphApplicationDlg::OnBnClickedCheckPanning()
{
	m_GraphCtrl.SetEditMode(CGraphCtrl::PanningMode);
	m_PanningCtrl.SetCheck(BST_CHECKED);
	m_NewVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_EditVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_MoveVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_DeleteVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEditEdges.SetCheck(BST_UNCHECKED);
	m_DeleteEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewVisitsCtrl.SetCheck(BST_UNCHECKED);
}

// OnBnClickedCheckNewVertices =================================================

void CGraphApplicationDlg::OnBnClickedCheckNewVertices()
{
	m_GraphCtrl.m_ViewportAjust = false;
	m_GraphCtrl.SetEditMode(CGraphCtrl::NewVerticesMode);
	m_PanningCtrl.SetCheck(BST_UNCHECKED);
	m_NewVerticesCtrl.SetCheck(BST_CHECKED);
	m_EditVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_MoveVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_DeleteVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEditEdges.SetCheck(BST_UNCHECKED);
	m_DeleteEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewVisitsCtrl.SetCheck(BST_UNCHECKED);
}

// OnBnClickedCheckEditVertices ================================================

void CGraphApplicationDlg::OnBnClickedCheckEditVertices()
{
	m_GraphCtrl.m_ViewportAjust = false;
	m_GraphCtrl.SetEditMode(CGraphCtrl::EditVerticesMode);
	m_PanningCtrl.SetCheck(BST_UNCHECKED);
	m_NewVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_EditVerticesCtrl.SetCheck(BST_CHECKED);
	m_MoveVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_DeleteVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEditEdges.SetCheck(BST_UNCHECKED);
	m_DeleteEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewVisitsCtrl.SetCheck(BST_UNCHECKED);
}

// OnBnClickedCheckMoveVertices ================================================

void CGraphApplicationDlg::OnBnClickedCheckMoveVertices()
{
	m_GraphCtrl.m_ViewportAjust = false;
	m_GraphCtrl.SetEditMode(CGraphCtrl::MoveVerticesMode);
	m_PanningCtrl.SetCheck(BST_UNCHECKED);
	m_NewVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_EditVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_MoveVerticesCtrl.SetCheck(BST_CHECKED);
	m_DeleteVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEditEdges.SetCheck(BST_UNCHECKED);
	m_DeleteEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewVisitsCtrl.SetCheck(BST_UNCHECKED);
}

// OnBnClickedCheckDeleteVertices ==============================================

void CGraphApplicationDlg::OnBnClickedCheckDeleteVertices()
{
	m_GraphCtrl.m_ViewportAjust = false;
	m_GraphCtrl.SetEditMode(CGraphCtrl::DeleteVerticesMode);
	m_PanningCtrl.SetCheck(BST_UNCHECKED);
	m_NewVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_EditVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_MoveVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_DeleteVerticesCtrl.SetCheck(BST_CHECKED);
	m_NewEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEditEdges.SetCheck(BST_UNCHECKED);
	m_DeleteEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewVisitsCtrl.SetCheck(BST_UNCHECKED);
}

// OnBnClickedCheckNewEdges ====================================================

void CGraphApplicationDlg::OnBnClickedCheckNewEdges()
{
	m_GraphCtrl.m_ViewportAjust = false;
	m_GraphCtrl.SetEditMode(CGraphCtrl::NewEdgesMode);
	m_PanningCtrl.SetCheck(BST_UNCHECKED);
	m_NewVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_EditVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_MoveVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_DeleteVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEdgesCtrl.SetCheck(BST_CHECKED);
	m_NewEditEdges.SetCheck(BST_UNCHECKED);
	m_DeleteEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewVisitsCtrl.SetCheck(BST_UNCHECKED);
}

// OnBnClickedCheckEditEdges ===================================================

void CGraphApplicationDlg::OnBnClickedCheckEditEdges()
{
	m_GraphCtrl.m_ViewportAjust = false;
	m_GraphCtrl.SetEditMode(CGraphCtrl::EditEdgesMode);
	m_PanningCtrl.SetCheck(BST_UNCHECKED);
	m_NewVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_EditVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_MoveVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_DeleteVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEditEdges.SetCheck(BST_CHECKED);
	m_DeleteEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewVisitsCtrl.SetCheck(BST_UNCHECKED);
}

// OnBnClickedCheckDeleteEdges =================================================

void CGraphApplicationDlg::OnBnClickedCheckDeleteEdges()
{
	m_GraphCtrl.m_ViewportAjust = false;
	m_GraphCtrl.SetEditMode(CGraphCtrl::DeleteEdgesMode);
	m_PanningCtrl.SetCheck(BST_UNCHECKED);
	m_NewVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_EditVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_MoveVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_DeleteVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEditEdges.SetCheck(BST_UNCHECKED);
	m_DeleteEdgesCtrl.SetCheck(BST_CHECKED);
	m_NewVisitsCtrl.SetCheck(BST_UNCHECKED);
}

// OnBnClickedCheckNewVisits ===================================================

void CGraphApplicationDlg::OnBnClickedCheckNewVisits()
{
	m_GraphCtrl.m_ViewportAjust = false;
	m_GraphCtrl.SetEditMode(CGraphCtrl::NewVisitsMode);
	m_PanningCtrl.SetCheck(BST_UNCHECKED);
	m_NewVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_EditVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_MoveVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_DeleteVerticesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewEditEdges.SetCheck(BST_UNCHECKED);
	m_DeleteEdgesCtrl.SetCheck(BST_UNCHECKED);
	m_NewVisitsCtrl.SetCheck(BST_CHECKED);
}

// OnBnClickedButtonCleanVisits ================================================

void CGraphApplicationDlg::OnBnClickedButtonCleanVisits()
{
	PrintLog("OnBnClickedButtonCleanVisits");
	m_Visits.Clear();
	m_GraphCtrl.Invalidate();
}


// OnBnClickedButtonLoadVisits =================================================

void CGraphApplicationDlg::OnBnClickedButtonLoadVisits()
{
	CFileDialog dlg(true, NULL, NULL, OFN_FILEMUSTEXIST,
		"Visits files (*.VIS)|*.VIS|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonLoadVisits %s", dlg.GetPathName());
		try {
			//m_Visits.Clear();
			//m_Track.Clear();
			m_Visits.Load(dlg.GetPathName());
			cout << "Visits   : " << dlg.GetPathName() << endl;
			cout << "Vertices: " << m_Visits.GetNVertices() << endl;
			//m_GraphCtrl.m_DrawDijkstraDistances = false;
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
		m_GraphCtrl.Show();
	}
}

// OnBnClickedButtonSaveVisits ================================================

void CGraphApplicationDlg::OnBnClickedButtonSaveVisits()
{
	CFileDialog dlg(false, ".VIS", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Visits files (*.VIS)|*.VIS|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonSaveVisits %s", dlg.GetPathName());
		try {
			m_Visits.Save(dlg.GetPathName());
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
	}
}

// OnBnClickedButtonCreateRandomVisits ==========================================

void CGraphApplicationDlg::OnBnClickedButtonCreateRandomVisits()
{
	CVisitsDimensionsDlg dlg;
	dlg.m_Visits = 4;
	dlg.m_Ciclic = false;
	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonCreateRandomVisits %d %s", dlg.m_Visits, dlg.m_Ciclic? "ciclic" : "");
		try {
			m_Visits.RandomCreation(dlg.m_Visits, dlg.m_Ciclic);
			cout << "Visitas aleatorias: " << dlg.m_Visits << " visits " << (dlg.m_Ciclic ? "ciclic" : "") << endl;
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
		m_GraphCtrl.Show();
	}
}


// OnBnClickedButtonLoadTrack ==================================================

void CGraphApplicationDlg::OnBnClickedButtonLoadTrack()
{
	CFileDialog dlg(true, NULL, NULL, OFN_FILEMUSTEXIST,
		"Track files (*.TRK)|*.TRK|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonLoadTrack %s", dlg.GetPathName());
		try {
			//m_Visits.Clear();
			//m_Track.Clear();
			m_Track.Load(dlg.GetPathName());
			cout << "Track : " << dlg.GetPathName() << endl;
			cout << "Edges : " << m_Track.GetNEdges() << endl;
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
		m_GraphCtrl.Show();
	}
}

// OnBnClickedButtonSaveTrack =================================================

void CGraphApplicationDlg::OnBnClickedButtonSaveTrack()
{
	CFileDialog dlg(false, ".TRK", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Track files (*.TRK)|*.TRK|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonSaveTrack %s", dlg.GetPathName());
		try {
			m_Track.Save(dlg.GetPathName());
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
	}
}

// OnBnClickedButtonCleanTrack =================================================

void CGraphApplicationDlg::OnBnClickedButtonCleanTrack()
{
	PrintLog("OnBnClickedButtonCleanTrack");
	m_Track.Clear();
	m_Track2.Clear();
	m_GraphCtrl.Invalidate();
}


// OnBnClickedButtonLoadSpanningTree ==========================================

void CGraphApplicationDlg::OnBnClickedButtonLoadSpanningTree()
{
	CFileDialog dlg(true, NULL, NULL, OFN_FILEMUSTEXIST,
		"Spanning Tree files (*.TRE)|*.TRE|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonLoadSpanningTree %s", dlg.GetPathName());
		try {
			//m_Visits.Clear();
			//m_Track.Clear();
			m_SpanningTree.Load(dlg.GetPathName());
			cout << "EDGES: " << m_SpanningTree.GetNEdges() << endl;
			cout << "LENGTH: " << m_SpanningTree.Length() << endl;
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
		m_GraphCtrl.Show();
	}
}


// OnBnClickedButtonSaveSpanningTree ===========================================

void CGraphApplicationDlg::OnBnClickedButtonSaveSpanningTree()
{
	CFileDialog dlg(false, ".TRE", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Spanning Tree files (*.TRE)|*.TRE|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonSaveSpanningTree %s", dlg.GetPathName());
		try {
			m_SpanningTree.Save(dlg.GetPathName());
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
	}
}

// OnBnClickedButtonCleanSpanningTree ==========================================

void CGraphApplicationDlg::OnBnClickedButtonCleanSpanningTree()
{
	PrintLog("OnBnClickedButtonCleanSpanningTree");
	m_SpanningTree.Clear();
	m_GraphCtrl.Invalidate();
}

// OnBnClickedButtonPrim =======================================================

void CGraphApplicationDlg::OnBnClickedButtonPrim()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo de Prim necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonPrim");
	cout << "PRIM" << endl;
	try {
		m_Graph.SetDistancesToEdgeLength();
		double t0 = Clock();
		m_SpanningTree = SpanningTreePrim(m_Graph);
		double t = Clock() - t0;
		cout << "Run time: " << t << "seg." << endl;
		cout << "EDGES: " << m_SpanningTree.GetNEdges() << endl;
		cout << "LENGTH: " << m_SpanningTree.Length() << endl;
		cout << m_SpanningTree << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonKruskal ====================================================

void CGraphApplicationDlg::OnBnClickedButtonKruskal()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo de kruskal necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonKruskal");
	cout << "KRUSKAL" << endl;
	try {
		m_Graph.SetDistancesToEdgeLength();
		double t0 = Clock();
		m_SpanningTree = SpanningTreeKruskal(m_Graph);
		double t = Clock() - t0;
		cout << "Run time: " << t << "seg." << endl;
		cout << "EDGES: " << m_SpanningTree.GetNEdges() << endl;
		cout << "LENGTH: " << m_SpanningTree.Length() << endl;
		cout << m_SpanningTree << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonDijkstra ===================================================

void CGraphApplicationDlg::OnBnClickedButtonDijkstra()
{
	try {
		m_Graph.SetDistancesToEdgeLength();
		CVertex* pStart = m_Graph.FindVertex("Start");
		if (!pStart) {
			if (m_Graph.m_Vertices.empty()) throw MyException("No es poden calcular distancies en un graf sense vertex");
			pStart = &m_Graph.m_Vertices.front();
		}
		PrintLog("OnBnClickedButtonDijkstra");
		cout << "DIJKSTRA" << endl;
		double t0 = Clock();
		Dijkstra(m_Graph, pStart);
		double t = Clock() - t0;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
		m_GraphCtrl.m_DisplayDistances = true;
		UpdateGrafDisplay();
	}
	catch (exception &ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
}



// OnBnClickedButtonDijkstraQueue ===================================================

void CGraphApplicationDlg::OnBnClickedButtonDijkstraQueue()
{
	try {
		m_Graph.SetDistancesToEdgeLength();
		CVertex* pStart = m_Graph.FindVertex("Start");
		if (!pStart) {
			if (m_Graph.m_Vertices.empty()) throw MyException("No es poden calcular distancies en un graf sense vertex");
			pStart = &m_Graph.m_Vertices.front();
		}
		PrintLog("OnBnClickedButtonDijkstraQueue");
		cout << "DIJKSTRA QUEUE" << endl;
		double t0 = Clock();
		DijkstraQueue(m_Graph, pStart);
		double t = Clock() - t0;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
		m_GraphCtrl.m_DisplayDistances = true;
		UpdateGrafDisplay();

	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
}

void CGraphApplicationDlg::OnBnClickedButtonDVertex()
{
	try {
		const int min_nodes = 15;
		const int max_nodes = 100;
		const int num_arestes = min_nodes * (min_nodes - 1) / 2; // = 105
		const int num_visites = 4;
		
		if (m_AnaliseGreedy) {
			cout << "Running greedy " << endl;
		}
		else if (m_AnaliseBTPur) {
			cout << "Running bt pur " << endl;
		}
		else if (m_AnaliseBTGreedy) {
			cout << "Running bt greedy " << endl;
		}
		else if (m_AnaliseBB1) {
			cout << "Running B&B1 " << endl;
		}
		else if (m_AnaliseBB2) {
			cout << "Running B&B2 " << endl;
		}
		else if (m_AnaliseBB3) {
			cout << "Running B&B3 " << endl;
		}

		for (int i = min_nodes; i < max_nodes; i++) {
			// 1. Generar graf aleatori amb els parametres seleccionats
			// 2. Crida funció que troba camí
			// 3. Contar el temps

			// cout << "Num Nodes " << i << " Num Arestes " << num_arestes << " Num Visites " << num_visites << endl;

			m_Visits.Clear();
			m_Track.Clear();
		
			m_Graph.RandomCreation(i, num_arestes);

			m_Graph.SetDistancesToEdgeLength();
			m_Visits.RandomCreation(num_visites, false);

			double t0 = Clock();
			if (m_AnaliseGreedy) {
				m_Track = SalesmanTrackGreedy(m_Graph, m_Visits);
			}else if(m_AnaliseBTPur) {
				m_Track = SalesmanTrackBacktracking(m_Graph, m_Visits);
			}
			else if (m_AnaliseBTGreedy){
				m_Track = SalesmanTrackBacktrackingGreedy(m_Graph, m_Visits);
			}
			else if (m_AnaliseBB1) {
				m_Track = SalesmanTrackBranchAndBound1(m_Graph, m_Visits);
			}
			else if (m_AnaliseBB2) {
				m_Track = SalesmanTrackBranchAndBound2(m_Graph, m_Visits);
			}
			else if (m_AnaliseBB3) {
				m_Track = SalesmanTrackBranchAndBound3(m_Graph, m_Visits);
			}
			
			double t = Clock() - t0;
			cout << t << endl;

		}

		cout << "FI DVertex" << endl;
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
}

void CGraphApplicationDlg::OnBnClickedButtonDArestes()
{
	try {
		const int num_nodes = 15;
		const int num_visites = 4;
		const int min_arestes = 15;
		const int max_arestes = 100;

		if (m_AnaliseGreedy) {
			cout << "Running greedy " << endl;
		}
		else if (m_AnaliseBTPur) {
			cout << "Running bt pur " << endl;
		}
		else if (m_AnaliseBTGreedy) {
			cout << "Running bt greedy " << endl;
		}
		else if (m_AnaliseBB1) {
			cout << "Running B&B1 " << endl;
		}
		else if (m_AnaliseBB2) {
			cout << "Running B&B2 " << endl;
		}
		else if (m_AnaliseBB3) {
			cout << "Running B&B3 " << endl;
		}


		for (int i = min_arestes; i < max_arestes; i++) {
			m_Visits.Clear();
			m_Track.Clear();
			
			
			m_Graph.RandomCreation(num_nodes, i);
			m_Graph.SetDistancesToEdgeLength();

			m_Visits.RandomCreation(num_visites, false);

			double t0 = Clock();
			if (m_AnaliseGreedy) {
				m_Track = SalesmanTrackGreedy(m_Graph, m_Visits);
			}
			else if (m_AnaliseBTPur) {
				m_Track = SalesmanTrackBacktracking(m_Graph, m_Visits);
			}
			else if (m_AnaliseBTGreedy) {
				m_Track = SalesmanTrackBacktrackingGreedy(m_Graph, m_Visits);
			}
			else if (m_AnaliseBB1) {
				m_Track = SalesmanTrackBranchAndBound1(m_Graph, m_Visits);
			}
			else if (m_AnaliseBB2) {
				m_Track = SalesmanTrackBranchAndBound2(m_Graph, m_Visits);
			}
			else if (m_AnaliseBB3) {
				m_Track = SalesmanTrackBranchAndBound3(m_Graph, m_Visits);
			}
			double t = Clock() - t0;
			cout << t << endl;

		}
		cout << "FI DArestes" << endl;
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
}

void CGraphApplicationDlg::OnBnClickedButtonDVisites()
{
	try {
		const int min_visites = 2;
		const int max_visites = 15;
		const int num_nodes = 50;
		const int num_arestes = 200;

		if (m_AnaliseGreedy) {
			cout << "Running greedy " << endl;
		}
		else if (m_AnaliseBTPur) {
			cout << "Running bt pur " << endl;
		}
		else if (m_AnaliseBTGreedy) {
			cout << "Running bt greedy " << endl;
		}
		else if (m_AnaliseBB1) {
			cout << "Running B&B1 " << endl;
		}
		else if (m_AnaliseBB2) {
			cout << "Running B&B2 " << endl;
		}
		else if (m_AnaliseBB3) {
			cout << "Running B&B3 " << endl;
		}

		for (int i = min_visites; i <= max_visites; i++) {
			m_Visits.Clear();
			m_Track.Clear();

			m_Graph.RandomCreation(num_nodes, num_arestes);
			m_Graph.SetDistancesToEdgeLength();
			m_Visits.RandomCreation(i, false);

			double t0 = Clock();
			if (m_AnaliseGreedy) {
				m_Track = SalesmanTrackGreedy(m_Graph, m_Visits);
			}
			else if (m_AnaliseBTPur) {
				m_Track = SalesmanTrackBacktracking(m_Graph, m_Visits);
			}
			else if (m_AnaliseBTGreedy) {
				m_Track = SalesmanTrackBacktrackingGreedy(m_Graph, m_Visits);
			}
			else if (m_AnaliseBB1) {
				m_Track = SalesmanTrackBranchAndBound1(m_Graph, m_Visits);
			}
			else if (m_AnaliseBB2) {
				m_Track = SalesmanTrackBranchAndBound2(m_Graph, m_Visits);
			}
			else if (m_AnaliseBB3) {
				m_Track = SalesmanTrackBranchAndBound3(m_Graph, m_Visits);
			}
			double t = Clock() - t0;
			cout << t << endl;
		}
		cout << "FI DVisites" << endl;
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
}
// OnBnClickedButtonGreedy =====================================================

void CGraphApplicationDlg::OnBnClickedButtonGreedy()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo SalesmanGreedy necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_Visits.m_Vertices.empty()) {
		AfxMessageBox("El algoritmo SalesmanGreedy necesita unas visitias para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonGreedy");
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "SALESMAN GREEDY" << endl;
		double t0 = Clock();
		m_Track = SalesmanTrackGreedy(m_Graph, m_Visits);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonBacktracking ===============================================

void CGraphApplicationDlg::OnBnClickedButtonBacktracking()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo Backtracking necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_Visits.m_Vertices.empty()) {
		AfxMessageBox("El algoritmo Backtracking necesita unas visitias para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonBacktracking");
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "SALESMAN BACKTRACKING" << endl;
		double t0 = Clock();
		m_Track = SalesmanTrackBacktracking(m_Graph, m_Visits);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonBacktrackingGreedy =========================================

void CGraphApplicationDlg::OnBnClickedButtonBacktrackingGreedy()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo BacktrackingGreedy necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_Visits.m_Vertices.empty()) {
		AfxMessageBox("El algoritmo BacktrackingGreedy necesita unas visitias para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonBacktrackingGreedy");
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "SALESMAN BACKTRACKING GREEDY" << endl;
		double t0 = Clock();
		m_Track = SalesmanTrackBacktrackingGreedy(m_Graph, m_Visits);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonBranchBound1 ===============================================

void CGraphApplicationDlg::OnBnClickedButtonBranchBound1()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo BranchAndBound1 necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_Visits.m_Vertices.empty()) {
		AfxMessageBox("El algoritmo BranchAndBound1 necesita unas visitias para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonBranchBound1");
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "SALESMAN BRANCH&BOUND 1" << endl;
		double t0 = Clock();
		m_Track = SalesmanTrackBranchAndBound1(m_Graph, m_Visits);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonBranchBound2 ===============================================

void CGraphApplicationDlg::OnBnClickedButtonBranchBound2()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo BranchAndBound2 necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_Visits.m_Vertices.empty()) {
		AfxMessageBox("El algoritmo BranchAndBound2 necesita unas visitias para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonBranchBound2");
	try {
		m_Graph.SetDistancesToEdgeLength();
		double t0 = Clock();
		m_Track = SalesmanTrackBranchAndBound2(m_Graph, m_Visits);
		cout << "SALESMAN BRANCH&BOUND 2" << endl;
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonBranchBound3 ===============================================

void CGraphApplicationDlg::OnBnClickedButtonBranchBound3()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo BranchAndBound3 necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_Visits.m_Vertices.empty()) {
		AfxMessageBox("El algoritmo BranchAndBound3 necesita unas visitias para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonBranchBound3");
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "SALESMAN BRANCH&BOUND 3" << endl;
		double t0 = Clock();
		m_Track = SalesmanTrackBranchAndBound3(m_Graph, m_Visits);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonProbabilistic ==============================================

void CGraphApplicationDlg::OnBnClickedButtonProbabilistic()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo Probabilistic necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_Visits.m_Vertices.empty()) {
		AfxMessageBox("El algoritmo Probabilistic necesita unas visitias para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonProbabilistic");
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "SALESMAN PROBABILISTIC" << endl;
		double t0 = Clock();
		m_Track = SalesmanTrackProbabilistic(m_Graph, m_Visits);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// UpdateGrafDisplay ===========================================================

void CGraphApplicationDlg::UpdateGrafDisplay()
{
	m_GraphCtrl.Invalidate();
}

// OnBnClickedCheckDisplayNames ================================================

void CGraphApplicationDlg::OnViewViewnames()
{
	PrintLog("OnBnClickedCheckDisplayNames");
	m_GraphCtrl.m_DisplayNames = !m_GraphCtrl.m_DisplayNames;
	UpdateGrafDisplay();
}

// OnBnClickedCheckDisplayVertices =============================================

void CGraphApplicationDlg::OnViewViewvertices()
{
	PrintLog("OnBnClickedCheckDisplayVertices");
	m_GraphCtrl.m_DisplayVertices = !m_GraphCtrl.m_DisplayVertices;
	UpdateGrafDisplay();
}

// OnBnClickedCheckDisplayEdges ================================================

void CGraphApplicationDlg::OnViewViewedges()
{
	PrintLog("OnBnClickedCheckDisplayEdges");
	m_GraphCtrl.m_DisplayEdges = !m_GraphCtrl.m_DisplayEdges;
	UpdateGrafDisplay();
}

// OnBnClickedCheckDisplayDistances ============================================

void CGraphApplicationDlg::OnViewViewdistances()
{
	PrintLog("OnBnClickedCheckDisplayDistances");
	m_GraphCtrl.m_DisplayDistances = !m_GraphCtrl.m_DisplayDistances;
	UpdateGrafDisplay();
}


// OnBnClickedCheckDisplayVisits ===============================================

void CGraphApplicationDlg::OnViewViewvisits()
{
	PrintLog("OnBnClickedCheckDisplayVisits");
	m_GraphCtrl.m_DisplayVisits = !m_GraphCtrl.m_DisplayVisits;
	UpdateGrafDisplay();
}

// OnBnClickedCheckDisplayTrack ================================================

void CGraphApplicationDlg::OnViewViewtrack()
{
	PrintLog("OnBnClickedCheckDisplayTrack");
	m_GraphCtrl.m_DisplayTrack = !m_GraphCtrl.m_DisplayTrack;
	UpdateGrafDisplay();
}


// OnBnClickedCheckDisplaySpanningTree =========================================

void CGraphApplicationDlg::OnViewViewspanningtree()
{
	PrintLog("OnBnClickedCheckDisplaySpanningTree");
	m_GraphCtrl.m_DisplaySpanningTree = !m_GraphCtrl.m_DisplaySpanningTree;
	UpdateGrafDisplay();
}

// OnBnClickedButtonTrobaCami1 =================================================

void CGraphApplicationDlg::OnBnClickedButtonTrobaCami1()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo TrobaCami1 necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonTrobaCami1");
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "TrobaCami 1" << endl;
		double t0 = Clock();
		m_Track = TrobaCami1(m_Graph);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonTrobaCami2 =================================================

void CGraphApplicationDlg::OnBnClickedButtonTrobaCami2()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo TrobaCami2 necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonTrobaCami2");
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "TrobaCami 2" << endl;
		double t0 = Clock();
		m_Track = TrobaCami2(m_Graph);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonTrobaCami3 =================================================

void CGraphApplicationDlg::OnBnClickedButtonTrobaCami3()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo TrobaCami3 necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonTrobaCami3");
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "TrobaCami 3" << endl;
		double t0 = Clock();
		m_Track = TrobaCami3(m_Graph);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonCleanConvexHull ============================================

void CGraphApplicationDlg::OnBnClickedButtonCleanConvexHull()
{
	PrintLog("OnBnClickedButtonCleanConvexHull");
	m_ConvexHull.Clear();
	m_GraphCtrl.Invalidate();
}

// OnBnClickedButtonLoadConvexHull =============================================

void CGraphApplicationDlg::OnBnClickedButtonLoadConvexHull()
{
	CFileDialog dlg(true, NULL, NULL, OFN_FILEMUSTEXIST,
		"Visits files (*.CH)|*.CH|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonLoadConvexHull %s", dlg.GetPathName());
		try {
			//m_Visits.Clear();
			//m_Track.Clear();
			m_ConvexHull.Load(dlg.GetPathName());
			cout << "ConvexHull   : " << dlg.GetPathName() << endl;
			cout << "Vertices: " << m_ConvexHull.GetNVertices() << endl;
			//m_GraphCtrl.m_DrawDijkstraDistances = false;
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
		m_GraphCtrl.Show();
	}
}

// OnBnClickedButtonSaveConvexHull =============================================

void CGraphApplicationDlg::OnBnClickedButtonSaveConvexHull()
{
	CFileDialog dlg(false, ".CH", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Visits files (*.CH)|*.CH|"
		"All Files (*.*)|*.*||"
	);

	if (dlg.DoModal() == IDOK) {
		PrintLog("OnBnClickedButtonSaveConvexHull %s", dlg.GetPathName());
		try {
			m_ConvexHull.Save(dlg.GetPathName());
		}
		catch (exception& ex) {
			PrintLog("ERROR: %s", ex.what());
			AfxMessageBox(CString(ex.what()), MB_OK | MB_ICONERROR);
		}
	}
}

//  OnBnClickedButtonQuickHull =================================================

void CGraphApplicationDlg::OnBnClickedButtonQuickHull()
{
	PrintLog("OnBnClickedButtonQuickHull");
	/*
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo QuickHull necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	*/
	try {
		m_Graph.SetDistancesToEdgeLength();
		cout << "QuickHull" << endl;
		double t0 = Clock();
		m_ConvexHull=QuickHull(m_Graph);
		double t = Clock() - t0;
		cout << "CONVEX HULL: " << m_ConvexHull << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}


void CGraphApplicationDlg::OnBnClickedButtonBreak()
{
	m_Break = true;
}


void CGraphApplicationDlg::OnBnClickedButtonContinue()
{
	m_Continue = true;
}

// WaitLoop ====================================================================

void WaitLoop()
{
	pGraphApplicationDlg->m_Break = false;
	pGraphApplicationDlg->m_Continue = false;
	pGraphApplicationDlg->m_BreakCtrl.ShowWindow(SW_SHOW);
	pGraphApplicationDlg->m_ContinueCtrl.ShowWindow(SW_SHOW);
	/*
	for (;;) {
		MSG message;
		if (::PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)) {
			if (!AfxPumpMessage()) {
				pGraphApplicationDlg->m_BreakCtrl.ShowWindow(SW_HIDE);
				pGraphApplicationDlg->m_ContinueCtrl.ShowWindow(SW_HIDE);
				cout << "SALIDA INESPERADA" << endl;
				break;
			}
		}
		if (pGraphApplicationDlg->m_Break) {
			pGraphApplicationDlg->m_BreakCtrl.ShowWindow(SW_HIDE);
			pGraphApplicationDlg->m_ContinueCtrl.ShowWindow(SW_HIDE);
			throw MyException("BREAK EXECUTION BY USER");

		}
		if (pGraphApplicationDlg->m_Continue) {
			pGraphApplicationDlg->m_BreakCtrl.ShowWindow(SW_HIDE);
			pGraphApplicationDlg->m_ContinueCtrl.ShowWindow(SW_HIDE);
			break;
		}
	}
	*/
	for (;;) {
		if (!AfxPumpMessage()) {
			pGraphApplicationDlg->m_BreakCtrl.ShowWindow(SW_HIDE);
			pGraphApplicationDlg->m_ContinueCtrl.ShowWindow(SW_HIDE);
			cout << "SALIDA INESPERADA" << endl;
			//::PostQuitMessage(0);
			//throw MyException("BREAK EXECUTION BY USER");
			break;
		}
		if (pGraphApplicationDlg->m_Break) {
			pGraphApplicationDlg->m_BreakCtrl.ShowWindow(SW_HIDE);
			pGraphApplicationDlg->m_ContinueCtrl.ShowWindow(SW_HIDE);
			throw MyException("BREAK EXECUTION BY USER");

		}
		if (pGraphApplicationDlg->m_Continue) {
			pGraphApplicationDlg->m_BreakCtrl.ShowWindow(SW_HIDE);
			pGraphApplicationDlg->m_ContinueCtrl.ShowWindow(SW_HIDE);
			break;
		}
	}
}

// OnBnClickedButtonTrobaCamiBB1 ===============================================

void CGraphApplicationDlg::OnBnClickedButtonTrobaCamiBB1()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo TrobaCamiBB necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonTrobaCamiBB1");
	try {
		m_Graph.SetDistancesToEdgeLength();
		m_Graph.ResetColor();
		cout << "TrobaCami branch&Bound" << endl;
		double t0 = Clock();
		m_Track = TrobaCamiBranchAndBound(m_Graph);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "SolutionNodesCreated=" << SolutionNodesCreated << endl;
		cout << "SolutionNodesBranched=" << SolutionNodesBranched << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonTrobaCamiBB2 ===============================================

void CGraphApplicationDlg::OnBnClickedButtonTrobaCamiBB2()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo TrobaCamiBranchAndBoundLink necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonTrobaCamiBB2");
	try {
		m_Graph.SetDistancesToEdgeLength();
		m_Graph.ResetColor();
		cout << "TrobaCami branch&Bound Link" << endl;
		double t0 = Clock();
		m_Track = TrobaCamiBranchAndBoundLink(m_Graph);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "SolutionNodesCreated=" << SolutionNodesCreated << endl;
		cout << "SolutionNodesBranched=" << SolutionNodesBranched << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonTrobaCamiBB4 ===============================================

void CGraphApplicationDlg::OnBnClickedButtonTrobaCamiBB4()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo TrobaCamiBranchAndBoundLink2 necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonTrobaCamiBB4");
	try {
		m_Graph.SetDistancesToEdgeLength();
		m_Graph.ResetColor();
		cout << "TrobaCami branch&Bound Link 2" << endl;
		double t0 = Clock();
		m_Track = TrobaCamiBranchAndBoundLink2(m_Graph);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "SolutionNodesCreated=" << SolutionNodesCreated << endl;
		cout << "SolutionNodesBranched=" << SolutionNodesBranched << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonTrobaCamiProgramacioDinamica ===============================

void CGraphApplicationDlg::OnBnClickedButtonTrobaCamiProgramacioDinamica()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo DijkstraQueueINICI_DESTI necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonTrobaCamiProgramacioDinamica");
	try {
		m_Graph.SetDistancesToEdgeLength();
		m_Graph.ResetColor();
		cout << "TrobaCami DijkstraQueueINICI_DESTI" << endl;
		double t0 = Clock();
		m_Track = DijkstraQueueINICI_DESTI(m_Graph);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "SolutionNodesCreated=" << SolutionNodesCreated << endl;
		cout << "SolutionNodesBranched=" << SolutionNodesBranched << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}

// OnBnClickedButtonTrobaCamiProgramacioDinamicaBB ===============================


void CGraphApplicationDlg::OnBnClickedButtonTrobaCamiProgramacioDinamicaBB()
{
	if (m_Graph.GetNVertices() == 0) {
		AfxMessageBox("El algoritmo TrobaCamiProgramacioDinamicaBB necesita un grafo para ejecutarse", MB_OK | MB_ICONERROR);
		return;
	}
	PrintLog("OnBnClickedButtonTrobaCamiProgramacioDinamicaBB");
	try {
		m_Graph.SetDistancesToEdgeLength();
		m_Graph.ResetColor();
		cout << "TrobaCami Programacio Dinamica i Branch&Bound" << endl;
		double t0 = Clock();
		m_Track = TrobaCamiProgramacioDinamicaBB(m_Graph);
		double t = Clock() - t0;
		cout << "TRACK: " << m_Track << endl;
		cout << "TRACK LENGTH: " << m_Track.Length() << endl;
		cout << "SolutionNodesCreated=" << SolutionNodesCreated << endl;
		cout << "SolutionNodesBranched=" << SolutionNodesBranched << endl;
		cout << "Run time: " << t << "seg." << endl;
		PrintLog("Run time: %f", t);
	}
	catch (exception& ex) {
		PrintLog("ERROR: %s", ex.what());
		cout << "EXCEPTION RUNNING ALGORITHM: " << ex.what() << endl;
	}
	m_GraphCtrl.Show();
}


void CGraphApplicationDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	if (nIndex == 3) {
		// menu View
		pPopupMenu->CheckMenuItem(ID_VIEW_VIEWNAMES, m_GraphCtrl.m_DisplayNames ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_VIEW_VIEWDISTANCES, m_GraphCtrl.m_DisplayDistances ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_VIEW_VIEWVERTICES, m_GraphCtrl.m_DisplayVertices ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_VIEW_VIEWEDGES, m_GraphCtrl.m_DisplayEdges ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_VIEW_VIEWVISITS, m_GraphCtrl.m_DisplayVisits ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_VIEW_VIEWTRACK, m_GraphCtrl.m_DisplayTrack ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_VIEW_VIEWSPANNINGTREE, m_GraphCtrl.m_DisplaySpanningTree ? MF_CHECKED : MF_UNCHECKED);
	}

	if (nIndex == 4) {
		// menu View
		pPopupMenu->CheckMenuItem(ID_ANALISIS_GREEDY, m_AnaliseGreedy ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_ANALISIS_BTPUR, m_AnaliseBTPur ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_ANALISIS_BTGREEDY, m_AnaliseBTGreedy ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_ANALISIS_BB1, m_AnaliseBB1 ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_ANALISIS_BB2, m_AnaliseBB2 ? MF_CHECKED : MF_UNCHECKED);
		pPopupMenu->CheckMenuItem(ID_ANALISIS_BB3, m_AnaliseBB3 ? MF_CHECKED : MF_UNCHECKED);
	}
}


void CGraphApplicationDlg::OnAnalisisGreedy()
{
	m_AnaliseGreedy = !m_AnaliseGreedy;
}


void CGraphApplicationDlg::OnAnalisisBtpur()
{
	m_AnaliseBTPur = !m_AnaliseBTPur;
}


void CGraphApplicationDlg::OnAnalisisBtgreedy()
{
	m_AnaliseBTGreedy = !m_AnaliseBTGreedy;
}


void CGraphApplicationDlg::OnAnalisisBb1()
{
	m_AnaliseBB1 = !m_AnaliseBB1;
}


void CGraphApplicationDlg::OnAnalisisBb2()
{
	m_AnaliseBB2 = !m_AnaliseBB2;
}


void CGraphApplicationDlg::OnAnalisisBb3()
{
	m_AnaliseBB3 = !m_AnaliseBB3;
}
