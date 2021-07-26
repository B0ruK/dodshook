#include "include.h"

HFont Fonts::m_MenuFont;
HFont Fonts::m_ListItemFont;
HFont Fonts::m_WatermarkFont;
HFont Fonts::m_VelocityFont;

void Draw::InitFonts()
{
	if (pSurface == nullptr)
		return;

	pSurface->SetFontGlyphSet(Fonts::m_MenuFont = pSurface->Create_Font(), "Visitor TT2 BRK", 15, 500, 0, 0, 0x200);
	pSurface->SetFontGlyphSet(Fonts::m_ListItemFont = pSurface->Create_Font(), "Visitor TT2 BRK", 13, 500, 0, 0, 0x200);
	pSurface->SetFontGlyphSet(Fonts::m_WatermarkFont = pSurface->Create_Font(), "Tahoma", 13, 700, 0, 0, 0x200);
	pSurface->SetFontGlyphSet(Fonts::m_VelocityFont = pSurface->Create_Font(), "Tahoma", 24, 700, 0, 0, 0x200);
}

void Draw::SoftOutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a)
{
	Draw::FillRGBA(x + 2, y, w - 3, 1, r, g, b, a);
	Draw::FillRGBA(x + 1, y + 1, 1, 1, r, g, b, a);
	Draw::FillRGBA(x, y + 2, 1, h - 3, r, g, b, a);
	Draw::FillRGBA(x + 1, y + h - 1, 1, 1, r, g, b, a);
	Draw::FillRGBA(x + w, y + 2, 1, h - 3, r, g, b, a);
	Draw::FillRGBA(x + w - 1, y + 1, 1, 1, r, g, b, a);
	Draw::FillRGBA(x + 2, y + h, w - 3, 1, r, g, b, a);
	Draw::FillRGBA(x + w - 1, y + h - 1, 1, 1, r, g, b, a);
}

void Draw::DrawStringA(unsigned long font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...)
{
	if (font == NULL || input == NULL)
		return;

	wchar_t wstr[128];
	char	cstr[256];

	va_list	va_alist;
	va_start(va_alist, input);
	vsprintf(cstr, input, va_alist);
	va_end(va_alist);

	MultiByteToWideChar(CP_UTF8, 0, cstr, -1, wstr, 128);

	if (center)
	{
		int w, h;
		pSurface->GetTextSize(font, wstr, w, h);

		if (w > 0)
			w /= 2;

		x -= w;
	}

	pSurface->DrawSetTextColor(r, g, b, a);
	pSurface->DrawSetTextFont(font);
	pSurface->DrawSetTextPos(x, y);
	pSurface->DrawPrintText(wstr, strlen(cstr));
}

void Draw::FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a)
{
	pSurface->DrawSetColor(r, g, b, a);
	pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void Draw::LineRGBA(int x, int y, int w, int h, int r, int g, int b, int a)
{
	pSurface->DrawSetColor(r, g, b, a);
	pSurface->DrawLine(x, y,w,h);
}

int iRed, iGreen, iBlue;
void Draw::GradientVertical(int x, int y, int w, int h, int r, int g, int b, int a, int r2, int g2, int b2)
{
	y += 1;

	for (int i = 1; i < h; i++)
	{
		iRed = (int)((float)i / h * (r - r2));
		iGreen = (int)((float)i / h * (g - g2));
		iBlue = (int)((float)i / h * (b - b2));
		Draw::FillRGBA(x, y + i - 1, w, 1, r - iRed, g - iGreen, b - iBlue, a);
	}
}

static bool screen_transform(const Vector& in, Vector& out)
{
	static auto& w2sMatrix = pEngine->WorldToScreen();

	out.x = w2sMatrix.m[0][0] * in.x + w2sMatrix.m[0][1] * in.y + w2sMatrix.m[0][2] * in.z + w2sMatrix.m[0][3];
	out.y = w2sMatrix.m[1][0] * in.x + w2sMatrix.m[1][1] * in.y + w2sMatrix.m[1][2] * in.z + w2sMatrix.m[1][3];
	out.z = 0.0f;

	float w = w2sMatrix.m[3][0] * in.x + w2sMatrix.m[3][1] * in.y + w2sMatrix.m[3][2] * in.z + w2sMatrix.m[3][3];

	if (w < 0.001f) {
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}

	out.x /= w;
	out.y /= w;

	return true;
}

bool Draw::WorldToScreen(const Vector& in, Vector& out)
{
	if (screen_transform(in, out)) 
	{
		int w, h;
		pEngine->GetScreenSize(w, h);

		out.x = (w / 2.0f) + (out.x * w) / 2.0f;
		out.y = (h / 2.0f) - (out.y * h) / 2.0f;

		return true;
	}
	return false;
}

void Draw::OutlinedRectangle(int x, int y, int w, int h, int r, int g, int b, int a)
{
	Draw::FillRGBA(x, y, w, 1, r, g, b, a);
	Draw::FillRGBA(x, y, 1, h, r, g, b, a);
	Draw::FillRGBA(x + w, y, 1, h + 1, r, g, b, a);
	Draw::FillRGBA(x, y + h, w, 1, r, g, b, a);
}