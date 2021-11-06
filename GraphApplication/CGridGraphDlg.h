#pragma once
#include "afxwin.h"
#include "Graph.h"

// Cuadro de diálogo de CGridGraphDlg

class CGridGraphDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGridGraphDlg)

public:
	CGridGraphDlg(CWnd* pParent = nullptr);   // Constructor estándar
	virtual ~CGridGraphDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GRID_GRAPH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_RowsSz;
	int m_ColumnsSz;
	virtual void OnOK();
};
