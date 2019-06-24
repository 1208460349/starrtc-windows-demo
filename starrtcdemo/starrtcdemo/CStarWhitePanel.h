#pragma once
#include <afxwin.h>


class CStarWhitePanel :
	public CStatic
{
public:
	CStarWhitePanel();
	~CStarWhitePanel();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnPaint();
public:
	//�򿪼����
	void laserPenOn();
	//�رռ����
	void laserPenOff();

private:
	bool m_bDraw;
	bool m_bLaserOn;
	CPoint m_StartPoint;
};

