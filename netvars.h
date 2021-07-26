#pragma once

class Netvarmanager
{
public:
	void Init();
	int GetOffset(const char *tableName, const char *propName);
private:
	int Get_Prop(const char *tableName, const char *propName, RecvProp **prop = 0);
	int Get_Prop(RecvTable *recvTable, const char *propName, RecvProp **prop = 0);
	RecvTable *GetTable(const char *tableName);
	std::vector<RecvTable*> m_tables;
};

extern Netvarmanager g_Netvarmanager;
