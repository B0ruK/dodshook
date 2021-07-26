#pragma once

struct RecvProp;

struct RecvTable
{
	RecvProp		*m_pProps;
	int				m_nProps;
	BYTE            Pad[4];
	char			*m_pNetTableName;
};

struct RecvProp
{
	char	  *m_pVarName;
	BYTE      PPad[36];
	RecvTable *m_pDataTable;
	int		  m_Offset;
	BYTE      Pad[12];
};

class ClientClass
{
public:
	BYTE         Pad[8];
	char*        GetName;
	RecvTable*	 GetTable;
	ClientClass* NextClass;
};