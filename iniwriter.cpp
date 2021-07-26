#include "iniwriter.h"
#include <iostream>
#include <Windows.h> 



CIniWriter::CIniWriter(const char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}
void CIniWriter::WriteFloat(char* szKey, float fltValue)
{
	char szValue[255];
	sprintf(szValue, "%f", fltValue);
	WritePrivateProfileStringA(szKey, szKey, szValue, m_szFileName);
}