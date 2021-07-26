#include "inireader.h"
#include <iostream>
#include <Windows.h>

CIniReader::CIniReader(const char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}

float CIniReader::ReadFloat(char* szKey)
{
	char szResult[255];
	float fltResult;
	GetPrivateProfileStringA(szKey, szKey, "0.00f", szResult, 255, m_szFileName);
	fltResult = atof(szResult);
	return fltResult;
}