#pragma once

#include "main.h"

class Label : public cgl::drawing::CGLLabel
{
private:
	IFW1Factory* m_pFactory;
	IFW1FontWrapper* m_pFontWrapper;

	cgl::PD3D11Effect m_pEffect;

public:
	Label(cgl::PD3D11Effect pEffect, int x, int y, int width, int height);
	~Label();
	void RenderText(std::string text);
};

