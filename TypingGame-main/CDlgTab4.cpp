// CDlgTab4.cpp: 구현 파일
//

#include "pch.h"
#include "TypingGame.h"
#include "afxdialogex.h"
#include "CDlgTab4.h"
#include "locale.h" // 추가
#include "afxtempl.h" // 추가?
#include "afxwin.h" //추가?
#include <afx.h> // CStdioFile 헤더 파일 포함
#include <afxstr.h> // CString 헤더 파일 포함



// CDlgTab4 대화 상자

IMPLEMENT_DYNAMIC(CDlgTab4, CDialogEx)

CDlgTab4::CDlgTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TAB_4_SCORE, pParent)
{

}

CDlgTab4::~CDlgTab4()
{
}

void CDlgTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTab4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDlgTab4::OnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CDlgTab4::OnClickedButtonUpdate)
	ON_WM_PAINT()
    ON_COMMAND(IDC_RADIO_GAME1, &CDlgTab4::OnRadioGame1)
    ON_COMMAND(IDC_RADIO_GAME2, &CDlgTab4::OnRadioGame2)
END_MESSAGE_MAP()


// CDlgTab4 메시지 처리기


void CDlgTab4::OnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (AfxMessageBox(_T("초기화를 진행하시겠습니까?"),
        MB_YESNO | MB_ICONQUESTION) == IDYES) {
        lines_prac.RemoveAll();
        CStdioFile file;

        file.Open(filePath_prac, CFile::modeWrite | CFile::modeCreate);
        Invalidate();
    }
}


void CDlgTab4::OnClickedButtonUpdate()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    lines_prac.RemoveAll();

    CStdioFile file;
    if (m_bType == 0){
        if (file.Open(filePath_prac, CFile::modeRead | CFile::typeText)) {
            CString strTmp;
            while (file.ReadString(strTmp)) {
                lines_prac.Add(strTmp);
            }
            file.Close();
        }
    }
    else {
        if (file.Open(filePath_rain, CFile::modeRead | CFile::typeText)) {
            CString strTmp;
            while (file.ReadString(strTmp)) {
                lines_rain.Add(strTmp);
            }
            file.Close();
        }
    }
	Invalidate();

}


void CDlgTab4::OnPaint()
{


    CPaintDC dc(this); // 디바이스 컨텍스트 얻기
    CRect clientRect;
    GetClientRect(&clientRect);
    // 간격 및 여백 설정
    int barWidth = 50;
    int barMargin = 70;

    int num = 0, index = 0;
    int maxIndex = 0, minIndex = 0;
    int maxSize = 0, minSize = INT_MAX;
    float sum = 0.0;
    CStringArray LINES;
    if (m_bType == 0) 
        LINES.Copy(lines_prac);
    else
        LINES.Copy(lines_rain);

    if (LINES.GetSize() > 7)
    {
        num = LINES.GetSize() - 7;
    }

    for (int i = num; i < LINES.GetSize(); i++)
    {
        CString str = LINES.GetAt(i);
        int score = _ttoi(str);
        if (score > maxSize)
        {
            maxSize = score;
            maxIndex = index;
        }

        if (score < minSize)
        {
            minSize = score;
            minIndex = index;
        }

        index++;
    }

    index = 0;
    for (int i = num; i < LINES.GetSize(); i++)
    {
        CString str = LINES.GetAt(i);
        int score = _ttoi(str);
        sum += score;
        int left = index * (barWidth + barMargin) + barMargin;
        int right = left + barWidth;
        int bottom = clientRect.bottom - 100;
        int top = bottom - score * 5;

        // Draw bar caption
        CRect rect(left, top, right, clientRect.bottom - 80);
        dc.DrawText(str, rect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);

        index++;

    }
    // 평균 추가
    CRect rect2(500, clientRect.bottom - 50, 600, clientRect.bottom - 20);
    CString scoreString;
    if (LINES.GetCount() == 0) {
        scoreString.Format(_T("평균 : 0.00"));
    }
    else
        scoreString.Format(_T("평균 : %.2f"), sum/LINES.GetSize()); // 정수를 문자열로 변환
    dc.DrawText(scoreString, rect2, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);

    // Draw bars with different colors
    index = 0;
    for (int i = num; i < LINES.GetSize(); i++)
    {
        CString str = LINES.GetAt(i);
        int score = _ttoi(str);

        int left = index * (barWidth + barMargin) + barMargin;
        int right = left + barWidth;
        int bottom = clientRect.bottom - 100;
        int top = bottom - score * 5;

        // Draw the bar with red color if it is the largest
        if (score == maxSize)
            dc.FillSolidRect(left, top, right - left, bottom - top, RGB(255, 0, 0));
        else if (score == minSize)
            // Draw the bar with blue color if it is the smallest
            dc.FillSolidRect(left, top, right - left, bottom - top, RGB(0, 0, 255));
        else
            // Draw other bars with the default color
            dc.Rectangle(left, top, right, bottom);

        index++;

    }
    // 가로
    dc.MoveTo(50, clientRect.bottom - 100);
    dc.LineTo(1100, clientRect.bottom - 100);
    // 세로
    dc.MoveTo(50, 50);
    dc.LineTo(50, clientRect.bottom - 100);
}


BOOL CDlgTab4::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  여기에 추가 초기화 작업을 추가합니다.
    //라디오버튼 추가
    CButton* pCheck = (CButton*)GetDlgItem(IDC_RADIO_GAME1);
    pCheck->SetCheck(1);
    m_bType = 0; // 0이 1번게임, prac

    CStdioFile file;
    setlocale(LC_ALL, "korea");

    // 1번 파일 열기
    if (file.Open(filePath_prac, CFile::modeRead | CFile::typeText)) {
        CString strTmp;
        while (file.ReadString(strTmp)) {
            lines_prac.Add(strTmp);
        }
        file.Close();
    }
    else {
        // 파일 열기 실패
        AfxMessageBox(_T("파일을 열 수 없습니다."));
    }
    //2번 파일 열기
    if (file.Open(filePath_rain, CFile::modeRead | CFile::typeText)) {
        CString strTmp;
        while (file.ReadString(strTmp)) {
            lines_rain.Add(strTmp);
        }
        file.Close();
    }
    else {
        // 파일 열기 실패
        AfxMessageBox(_T("파일을 열 수 없습니다."));
    }
    return TRUE;

    // return TRUE unless you set the focus to a control
    // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgTab4::OnRadioGame1()
{
    // TODO: 여기에 명령 처리기 코드를 추가합니다.
    m_bType = 0;
    Invalidate();
}


void CDlgTab4::OnRadioGame2()
{
    // TODO: 여기에 명령 처리기 코드를 추가합니다.
    m_bType = 1;
    Invalidate();
}
