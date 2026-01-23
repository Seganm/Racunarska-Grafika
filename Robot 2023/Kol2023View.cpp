
// Kol2023View.cpp : implementation of the CKol2023View class
//

#include "pch.h"
#include <corecrt_math_defines.h>
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kol2023.h"
#endif

#include "Kol2023Doc.h"
#include "Kol2023View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DImage.h"


// CKol2023View

IMPLEMENT_DYNCREATE(CKol2023View, CView)

BEGIN_MESSAGE_MAP(CKol2023View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKol2023View construction/destruction

CKol2023View::CKol2023View() noexcept
{
	// TODO: add construction code here
	glava = new DImage();
	glava->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\I kolokvijum 2023 - resursi\\glava.png"));
	podlaktica = new DImage();
	podlaktica->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\I kolokvijum 2023 - resursi\\podlaktica.png"));
	nadlaktica = new DImage();
	nadlaktica->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\I kolokvijum 2023 - resursi\\nadlaktica.png"));
	nadkolenica = new DImage();
	nadkolenica->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\I kolokvijum 2023 - resursi\\nadkolenica.png"));
	podkolenica = new DImage();
	podkolenica->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\I kolokvijum 2023 - resursi\\podkolenica.png"));
	saka = new DImage();
	saka->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\I kolokvijum 2023 - resursi\\saka.png"));
	stopalo = new DImage();
	stopalo->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\I kolokvijum 2023 - resursi\\stopalo.png"));
	telo = new DImage();
	telo->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\I kolokvijum 2023 - resursi\\telo.png"));
	pozadina = new DImage();
	pozadina->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\I kolokvijum 2023 - resursi\\pozadina.jpg"));

}

CKol2023View::~CKol2023View()
{
	delete glava;
	delete telo;
	delete saka;
	delete stopalo;
	delete pozadina;
	delete nadkolenica;
	delete nadlaktica;
	delete podlaktica;
	delete podkolenica;
}

void CKol2023View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM xform;
	xform.eM11 = cos(angle * M_PI / 180);
	xform.eM12 = sin(angle * M_PI / 180);
	xform.eM21 = -sin(angle * M_PI / 180);
	xform.eM22 = cos(angle * M_PI / 180);
	xform.eDx = 0;
	xform.eDy = 0;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CKol2023View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xform;
	xform.eM11 = 1;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 = 1;
	xform.eDx = dX;
	xform.eDy = dY;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CKol2023View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM xform;
	xform.eM11 = sX;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 = sY;
	xform.eDx = 0;
	xform.eDy = 0;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

BOOL CKol2023View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


void CKol2023View::DrawBackground(CDC* pDC)
{
	int w = pozadina->Width();
	int h = pozadina->Height();

	CRect rect(0, 0, w, h);

	pozadina->Draw(pDC, rect, rect);
}


void CKol2023View::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	BYTE* bytes = pImage->GetDIBBits();
	COLORREF color = RGB(bytes[2], bytes[1], bytes[0]);

	int w = pImage->Width();
	int h = pImage->Height();
	CRect rect(0, 0, w, h);

	pImage->DrawTransparent(pDC, rect, rect, color);
}

void CKol2023View::DrawHalf(CDC* pDC)
{
	XFORM xform;
	pDC->GetWorldTransform(&xform);


	Translate(pDC, -telo->Width(), -telo->Height(), false);
	DrawImgTransparent(pDC, telo);


	Translate(pDC, 25, 65, false);
	Rotate(pDC, nadlakticaUgao, false);
	Translate(pDC, -35,-35 , false);
	DrawImgTransparent(pDC, nadlaktica);


	Translate(pDC, 22, 167, false);
	Rotate(pDC, podlakticaUgao, false);
	Translate(pDC, -30, -33, false);
	DrawImgTransparent(pDC, podlaktica);

	Translate(pDC, 30, 140, false);
	Rotate(pDC, sakaUgao, false);
	Translate(pDC, -25, -3, false);
	DrawImgTransparent(pDC, saka);


	pDC->SetWorldTransform(&xform);
	Translate(pDC, -telo->Width(), -telo->Height(), false);
	Translate(pDC, 61-29, 262-20, false);
	DrawImgTransparent(pDC, nadkolenica);

	Translate(pDC, 30 - 25, 184 - 37, false);
	DrawImgTransparent(pDC, podkolenica);


	Translate(pDC,25-20, 248 - 16, false);
	DrawImgTransparent(pDC, stopalo);

	pDC->SetWorldTransform(&xform);
}


void CKol2023View::DrawHead(CDC* pDC)
{
	DrawImgTransparent(pDC, glava);
}

void  CKol2023View::DrawRobot(CDC* pDC)
{
	XFORM xform;
	pDC->GetWorldTransform(&xform);

	Translate(pDC, -50, -425, false);
	DrawHead(pDC);
	pDC->SetWorldTransform(&xform);
	DrawHalf(pDC);
	Scale(pDC, -1, 1, false);
	DrawHalf(pDC);
}
// CKol2023View drawing

void CKol2023View::OnDraw(CDC* pDC)
{
	CKol2023Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	//Antiflicker prvi deo
	CRect rect;
	GetClientRect(&rect);
	CDC* pMemDC = new CDC();
	pMemDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pMemDC->SelectObject(&bmp);

	int prevMode = pMemDC->SetGraphicsMode(GM_ADVANCED);
	XFORM XformOld;
	pMemDC->GetWorldTransform(&XformOld);
	DrawBackground(pMemDC);
	Translate(pMemDC, pozadina->Width() / 2, pozadina->Height() / 2, false);
	Scale(pMemDC, skaliranje, skaliranje, false);
	Rotate(pMemDC, ceo, false);
	DrawRobot(pMemDC);

	pMemDC->SetWorldTransform(&XformOld);

	//Antifliker drugi deo
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), pMemDC, 0, 0, SRCCOPY);
	pMemDC->DeleteDC();
	delete pMemDC;



	// TODO: add draw code for native data here
}



// CKol2023View printing

BOOL CKol2023View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKol2023View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKol2023View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKol2023View diagnostics

#ifdef _DEBUG
void CKol2023View::AssertValid() const
{
	CView::AssertValid();
}


void CKol2023View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKol2023Doc* CKol2023View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKol2023Doc)));
	return (CKol2023Doc*)m_pDocument;
}
#endif //_DEBUG


// CKol2023View message handlers



//Za Antiflikering
BOOL CKol2023View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	// TODO: Add your message handler code here and/or call default
}


void CKol2023View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if ((nChar == 'A' || nChar == 'a') && sakaUgao > -10)
		sakaUgao -= 10;
	if ((nChar == 'S' || nChar == 's') && sakaUgao < 30)
		sakaUgao += 10;
	if ((nChar == 'D' || nChar == 'd') && podlakticaUgao > -10)
		podlakticaUgao -= 10;
	if ((nChar == 'F' || nChar == 'f') && podlakticaUgao < 80)
		podlakticaUgao += 10;
	if ((nChar == 'G' || nChar == 'g') && nadlakticaUgao > -10)
		nadlakticaUgao -= 10;
	if ((nChar == 'H' || nChar == 'h') && nadlakticaUgao < 90)
		nadlakticaUgao += 10;
	if (nChar == '1')
	{
		ceo -= 10;
		skaliranje -= 0.1;
	}
	if (nChar == '2')
	{
		ceo += 10;
		skaliranje += 0.1;
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
