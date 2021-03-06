//**********************************************************************//
// Project:	HaRiBO MU GameServer - Season 6								//
// Company: RealCoderZ MU Development � 2010							//
// Description: MU StatManage Functions & Structures					//
// Decompilation By: Deathway											//
// Coded & Modified By:	WolF & M.E.S									//
//**********************************************************************//
#ifndef STATMNG_H
#define STATMNG_H


#define STAT_TABLE_SIZE	500


class CStatMng
{
public:
	CStatMng();
	virtual ~CStatMng();
	// -----
	void	Init();
	int		GetMaxStat(int level, int Class);
	int		GetMaxMinusStat(int iLevel, int iClass);
	// -----
private:
	int		gObjNormalAddStatTable[STAT_TABLE_SIZE];
	int		gObjMagumAddStatTable[STAT_TABLE_SIZE];
	int		gObjDarkLordAddStatTable[STAT_TABLE_SIZE];
	int		gObjNormalMinusStatTable[STAT_TABLE_SIZE];
	int		gObjMagumMinusStatTable[STAT_TABLE_SIZE];
	int		gObjDarkLordMinusStatTable[STAT_TABLE_SIZE];
};
extern CStatMng gStatMng;


#endif