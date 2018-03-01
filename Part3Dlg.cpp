
// Part3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Part3.h"
#include "Part3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPart3Dlg dialog



CPart3Dlg::CPart3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPart3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPart3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SimSpeedCB);
	DDX_Control(pDX, IDC_EDIT1, m_SimDataFileTF);
	DDX_Control(pDX, IDOK, m_EndSimButton);
	DDX_Control(pDX, IDC_BUTTON1, m_RunSimButton);
}

BEGIN_MESSAGE_MAP(CPart3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPart3Dlg::OnBnClickedButton1)
	ON_WM_TIMER (&CPart3Dlg::OnTimer)
END_MESSAGE_MAP()


// CPart3Dlg message handlers

BOOL CPart3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_SimSpeedCB.AddString(" 1X");
	m_SimSpeedCB.AddString(" 2X");
	m_SimSpeedCB.AddString("5X");


	// Resize and reposition the window
	m_iWinWidth = 1024;
	m_iWinHeight = 1074;
	this->SetWindowPos(NULL, 10, 10, m_iWinWidth, m_iWinHeight, 0); // Move and resize window
	// Move all the widgets
	m_EndSimButton.SetWindowPos(NULL, m_iWinWidth-150, m_iWinHeight-50, 100, 20, 0);
	m_RunSimButton.SetWindowPos(NULL, m_iWinWidth-275, m_iWinHeight-50, 100, 20, 0);
	m_SimSpeedCB.SetWindowPos(NULL, m_iWinWidth-350, m_iWinHeight-50, 50, 20, 0);
	m_SimDataFileTF.SetWindowPos(NULL, m_iWinWidth-675, m_iWinHeight-50, 200, 20, 0);
	// Move the sim speed label
	CStatic *label = (CStatic *)GetDlgItem(IDC_STATIC2);
	label->SetWindowPos(NULL, m_iWinWidth-450, m_iWinHeight-50, 200, 20, 0);
	// Move the data file label
	label = (CStatic *)GetDlgItem(IDC_STATIC1);
	label->SetWindowPos(NULL, m_iWinWidth-775, m_iWinHeight-50, 200, 20, 0);	char speedStr[10];
	// Get the name of the data file from the text field
	m_SimDataFileTF.GetWindowText(datafile, 63);
	// Get the speed to run
	m_SimSpeedCB.GetLBText(m_SimSpeedCB.GetCurSel(), speedStr);
	if(strcmp(speedStr, " 1X") == 0) CWnd::SetTimer(1, 1000, 0);
	else if(strcmp(speedStr, " 2X") == 0) CWnd::SetTimer(1, 500, 0);
	else CWnd::SetTimer(1, 200, 0);

	trafficSim = Simulation::getInstance();
	dataParser = dataParser->getInstance();
	dataParser->setDataFileName(datafile);
	trafficSim->build(dataParser);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPart3Dlg::OnTimer(UINT nIDEvent)
{
	// Perform any updates to the traffic sim state here before calling OnPaint
	m_dSimTime += 1.0; // Update sim time-member variable defined in programNameDlg.h
	trafficSim->update(m_dSimTime);
	OnPaint(); // Call the paint function to update the display
	CDialog::OnTimer(nIDEvent); // Pass on to super
}

void CPart3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPart3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		trafficSim->draw();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPart3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPart3Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here	// Create a couple of K&R strings
	char speedStr[10];
	// Get the speed to run
	m_SimSpeedCB.GetLBText(m_SimSpeedCB.GetCurSel(), speedStr);
	if(strcmp(speedStr, " 1X") == 0) CWnd::SetTimer(1, 1000, 0);
	else if(strcmp(speedStr, " 2X") == 0) CWnd::SetTimer(1, 500, 0);
	else CWnd::SetTimer(1, 200, 0);
	m_dSimTime = 0.0; // Init sim time-member variable defined in Prog3Dlg.h
	 // Disable the run sim button so the user can't click it again
	m_RunSimButton.EnableWindow(false);
	ts->run(); // It's kickoff time
}
