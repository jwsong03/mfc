
// chapter5_1View.cpp : Cchapter5_1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "chapter5_1.h"
#endif

#include "chapter5_1Doc.h"
#include "chapter5_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cchapter5_1View

IMPLEMENT_DYNCREATE(Cchapter5_1View, CView)

BEGIN_MESSAGE_MAP(Cchapter5_1View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cchapter5_1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cchapter5_1View ����/�Ҹ�

Cchapter5_1View::Cchapter5_1View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

Cchapter5_1View::~Cchapter5_1View()
{
}

BOOL Cchapter5_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// Cchapter5_1View �׸���

void Cchapter5_1View::OnDraw(CDC* /*pDC*/)
{
	Cchapter5_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// Cchapter5_1View �μ�


void Cchapter5_1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cchapter5_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void Cchapter5_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void Cchapter5_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void Cchapter5_1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cchapter5_1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cchapter5_1View ����

#ifdef _DEBUG
void Cchapter5_1View::AssertValid() const
{
	CView::AssertValid();
}

void Cchapter5_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cchapter5_1Doc* Cchapter5_1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cchapter5_1Doc)));
	return (Cchapter5_1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cchapter5_1View �޽��� ó����
