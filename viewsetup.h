#pragma once

class CViewSetup
{
public:
	uint32_t x;
	uint32_t m_nUnscaledX;
	uint32_t y;
	uint32_t m_nUnscaledY;
	uint32_t width; 
	uint32_t m_nUnscaledWidth; 
	uint32_t height;
	uint32_t m_eStereoEye;
	uint32_t m_nUnscaledHeight;
	bool m_bOrtho;
	float m_OrthoLeft;
	float m_OrthoTop;
	float m_OrthoRight;
	float m_OrthoBottom;
	float m_fov; 
};