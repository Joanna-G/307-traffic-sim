
// Part3Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Inclusions.h"
#include "TrafficSimDataParser.h"
#include "Simulation.h"


// CPart3Dlg dialog
class CPart3Dlg : public CDialogEx
{
// Construction
public:
	CPart3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PART3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT TimerVal);

public:
	afx_msg void OnBnClickedButton1();
	CComboBox m_SimSpeedCB;
	CEdit m_SimDataFileTF;

private:
	int m_iWinWidth;
	int m_iWinHeight;
	double m_dSimTime;
	char datafile[64];
	TrafficSimDataParser *dataParser;
	Simulation *trafficSim;

public:
	CButton m_EndSimButton;
	CButton m_RunSimButton;
	
};
