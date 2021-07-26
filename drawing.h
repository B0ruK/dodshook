#pragma once


typedef unsigned long HFont;

namespace Fonts
{
	extern HFont m_MenuFont;
	extern HFont m_ListItemFont;
	extern HFont m_WatermarkFont;
	extern HFont m_VelocityFont;
}

namespace Draw
{
	void InitFonts();
	void SoftOutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a);
	void DrawStringA(unsigned long font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...);
	void FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a);
	bool WorldToScreen(const Vector& in, Vector& out);
	void LineRGBA(int x, int y, int w, int h, int r, int g, int b, int a);
	void OutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a);
	void GradientVertical(int x, int y, int w, int h, int r, int g, int b, int a, int r2, int g2, int b2);
}

