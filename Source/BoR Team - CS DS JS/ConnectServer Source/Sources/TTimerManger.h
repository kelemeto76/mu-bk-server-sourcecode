//-------------------------------------------------------------------------------------------------------------------------------------------
#ifndef CTIMER_MANAGER_H
#define CTIMER_MANAGER_H
//-------------------------------------------------------------------------------------------------------------------------------------------

class CTimerManager : public CTimer
{
public:
	CTimerManager(void);
	~CTimerManager(void);
	// ----
	void OnSecond();
	void OnMinute(){};
	void OnHour(){};
	void OnDay(){};
};
//-------------------------------------------------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------------------------------------------------