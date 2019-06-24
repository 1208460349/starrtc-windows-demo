#include "stdafx.h"
#include "CStarWhitePanel.h"


CStarWhitePanel::CStarWhitePanel()
{
	m_bDraw = false;
	m_bLaserOn = false;
}


CStarWhitePanel::~CStarWhitePanel()
{
	m_bDraw = false;
}
BEGIN_MESSAGE_MAP(CStarWhitePanel, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//ON_WM_PAINT()
END_MESSAGE_MAP()


void CStarWhitePanel::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	AfxMessageBox("111");
	m_bDraw = true;
	m_StartPoint = point;
	CStatic::OnLButtonDown(nFlags, point);
}


void CStarWhitePanel::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	if (m_bDraw)
	{
		dc.MoveTo(m_StartPoint);
		dc.LineTo(point);
		m_StartPoint = point;
	}
	CStatic::OnMouseMove(nFlags, point);
}


void CStarWhitePanel::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bDraw = false;
	CStatic::OnLButtonUp(nFlags, point);
}
//
//
//void CStarWhitePanel::OnPaint()
//{
//	CPaintDC dc(this); 
//	//dc.SetBkMode(TRANSPARENT);
//}
//
//�򿪼����
void CStarWhitePanel::laserPenOn()
{
	m_bLaserOn = true;
}
//�رռ����
void CStarWhitePanel::laserPenOff()
{
	m_bLaserOn = false;
}
