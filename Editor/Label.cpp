#include "main.h"

Label::Label(cgl::PD3D11Effect pEffect, int x, int y, int width, int height)
	: cgl::drawing::CGLLabel(pEffect, width, height)
{
	SetX((float)x);
	SetY((float)y);

	m_pFactory = NULL;
	m_pFontWrapper = NULL;
	FW1CreateFactory(FW1_VERSION, &m_pFactory);

	m_pFactory->CreateFontWrapper(Device(), L"Consolas", &m_pFontWrapper);
}

void Label::RenderText( std::string text )
{
	FW1_RECTF rect;
	rect.Left = 5.0f;
	rect.Top = 5.0f;
	rect.Right = GetWidth() - 5.0f;
	rect.Bottom = GetHeight() - 5.0f;

	wstringstream wss; 
	wss.precision(2);
	wss << fixed << text.c_str();

	m_pFontWrapper->DrawString(Context(), wss.str().c_str(), L"Consolas", 18, &rect, 0xffffffff, NULL, NULL, FW1_RESTORESTATE | FW1_LEFT);
}

Label::~Label()
{
	SAFE_RELEASE(m_pFactory);
	SAFE_RELEASE(m_pFontWrapper);
}
