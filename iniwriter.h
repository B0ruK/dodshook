#pragma once


class CIniWriter
{
public:
	CIniWriter(const char* szFileName);
	void WriteFloat(char* szKey, float fltValue);
private:
	char m_szFileName[255];
};