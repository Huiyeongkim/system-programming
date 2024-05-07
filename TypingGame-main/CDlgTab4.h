#pragma once
#include "afxdialogex.h"


// CDlgTab4 대화 상자

class CDlgTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTab4)

public:
	CDlgTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgTab4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TAB_4_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonReset();
	afx_msg void OnClickedButtonUpdate();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CStringArray lines_prac;
	CStringArray lines_rain;

	CString filePath_prac = _T("C:\\Temp\\pracScore.txt");
	CString filePath_rain = _T("C:\\Temp\\rainScore.txt");
	BOOL m_bType;
	afx_msg void OnRadioGame1();
	afx_msg void OnRadioGame2();
};
