
// chapter5_1View.h : Cchapter5_1View Ŭ������ �������̽�
//

#pragma once


class Cchapter5_1View : public CView
{
protected: // serialization������ ��������ϴ�.
	Cchapter5_1View();
	DECLARE_DYNCREATE(Cchapter5_1View)

// Ư���Դϴ�.
public:
	Cchapter5_1Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~Cchapter5_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // chapter5_1View.cpp�� ����� ����
inline Cchapter5_1Doc* Cchapter5_1View::GetDocument() const
   { return reinterpret_cast<Cchapter5_1Doc*>(m_pDocument); }
#endif

