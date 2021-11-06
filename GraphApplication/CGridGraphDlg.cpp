// CGridGraphDlg.cpp: archivo de implementación
//

#include "pch.h"
#include "framework.h"
#include "GraphApplication.h"
#include "CGridGraphDlg.h"
#include "afxdialogex.h"

// Cuadro de diálogo de CGridGraphDlg

IMPLEMENT_DYNAMIC(CGridGraphDlg, CDialogEx)

CGridGraphDlg::CGridGraphDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_DIALOG_GRID_GRAPH, pParent)
	, m_RowsSz(0)
	, m_ColumnsSz(0)
{

}

CGridGraphDlg::~CGridGraphDlg()
{
}

void CGridGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ROWS, m_RowsSz);
	DDX_Text(pDX, IDC_EDIT_COLUMNS, m_ColumnsSz);
}


BEGIN_MESSAGE_MAP(CGridGraphDlg, CDialogEx)
END_MESSAGE_MAP()


// Controladores de mensajes de CGridGraphDlg


void CGridGraphDlg::OnOK()
{
	// TODO: Agregue aquí su código especializado o llame a la clase base
	if (UpdateData(true)) {
		if (m_RowsSz <= 0) {
			AfxMessageBox("Rows minimun value is 1", MB_OK | MB_ICONERROR);
			return;
		}
		if (m_ColumnsSz <= 0) {
			AfxMessageBox("Columns minimun value is 1", MB_OK | MB_ICONERROR);
			return;
		}
		CDialogEx::OnOK();
	}

}
