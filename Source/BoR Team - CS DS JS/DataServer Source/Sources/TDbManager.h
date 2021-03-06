//-------------------------------------------------------------------------------------------------------------------------------------------
#ifndef CDBMANAGER_H
#define CDBMANAGER_H
//-------------------------------------------------------------------------------------------------------------------------------------------

class CDbManager : public CDataBase
{
public:
	CDbManager(void);
	~CDbManager(void);
	// ----
	void OnMessage(const char * szMessage, ...);
	void OnError(const char * szMessage, ...);
	void OnQuery(const char * szMessage, ...);
};
//-------------------------------------------------------------------------------------------------------------------------------------------

extern CDbManager	g_DbManager;
//-------------------------------------------------------------------------------------------------------------------------------------------
#endif /* CDBMANAGER_H */
//-------------------------------------------------------------------------------------------------------------------------------------------
