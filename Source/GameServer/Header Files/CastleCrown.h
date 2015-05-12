//---------------------------------------------------------------------------
// # Project:		HaRiBO MU GameServer - Supported Season 6
// # Company:		RealCoderZ MU Development � 2011
// # Description:	Castle Crown Class
// # Developed By:	WolF & M.E.S
//---------------------------------------------------------------------------
#ifndef CASTLE_CROWN_H
#define CASTLE_CROWN_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ---------------------------------------------------------------------------------------------------------------------------------------------------
#if (GS_CASTLE)
// ---------------------------------------------------------------------------------------------------------------------------------------------------
class CCastleCrown 
{
public:
	CCastleCrown();
	virtual ~CCastleCrown();
	void CastleCrownAct(int iIndex);
};
// ---------------------------------------------------------------------------------------------------------------------------------------------------
extern CCastleCrown g_CsNPC_CastleCrown;
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#endif
