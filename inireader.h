#pragma once



class CIniReader
{
public:
	CIniReader(const char* szFileName);
	float ReadFloat(char* szKey);
private:
	char m_szFileName[255];
};