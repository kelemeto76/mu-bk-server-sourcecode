// TMonsterAIAutomata.cpp: implementation of the TMonsterAIAutomata class.
//	GS-N	2.00.05 JPN 0x0055BC30	-	Completed
//////////////////////////////////////////////////////////////////////

#include "../Header Files/stdafx.h"
#include "../Header Files/TMonsterAIAutomata.h"
#include "../Header Files/TMonsterAIGroup.h"
#include "../Header Files/TMonsterAIUtil.h"

#include "../Header Files/LogProc.H"
#include "../Header Files/ReadScript.h"

BOOL TMonsterAIAutomata::s_bDataLoad = FALSE;
TMonsterAIAutomata TMonsterAIAutomata::s_MonsterAIAutomataArray[MAX_MONSTER_AI_AUTOMATA];
static TMonsterAIUtil MONSTER_UTIL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TMonsterAIAutomata::TMonsterAIAutomata()
{
	this->Reset();
}

TMonsterAIAutomata::~TMonsterAIAutomata()
{
	return;
}



void TMonsterAIAutomata::Reset()
{
	for ( int i=0;i<MAX_AI_STATE;i++)
	{
		for ( int j=0;j<MAX_AI_PRIORITY;j++)
		{
			this->m_AIState[i][j].Reset();
		}
	}

	for ( int k=0;k<MAX_AI_STATE;k++)
	{
		this->m_AIStateTransCount[k] = 0;
	}

	this->m_iAutomataNumber = -1;
}


BOOL TMonsterAIAutomata::LoadData(const char* lpszFileName)
{
	TMonsterAIAutomata::s_bDataLoad = FALSE;

	if ( lpszFileName == NULL || strcmp(lpszFileName, "") == 0 )
	{
		CLog.MsgBox("[Monster AI Automata] - File load error : File Name Error");
		return FALSE;
	}

	try
	{
		SMDToken Token;
		SMDFile = fopen(lpszFileName, "r");

		if ( SMDFile == NULL )
		{
			CLog.MsgBox("[Monster AI Automata] - Can't Open %s ", lpszFileName);
			return FALSE;
		}

		TMonsterAIAutomata::DelAllAutomata();

		int iType = -1;

		while ( true )
		{
			Token = (SMDToken)GetToken();

			if ( Token == END )
				break;

			iType = (int)TokenNumber;

			while ( true )
			{
				if ( iType == 0 )
				{
					char szStateTransitionDesc[100] = {0};
					int iAutomataNumber = -1;
					int iPriority = -1;
					int iCurrentState = -1;
					int iNextState = -1;
					int iTransitionType = -1;
					int iTransitionRate = -1;
					int iTransitionValueType = -1;
					int iTransitionValue = -1;
					int iDelayTime = -1;

					Token = (SMDToken)GetToken();

					if ( strcmp("end", TokenString) == 0 )
						break;

					iAutomataNumber = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					memcpy(szStateTransitionDesc, TokenString, sizeof(szStateTransitionDesc));

					Token = (SMDToken)GetToken();
					iPriority = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iCurrentState = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iNextState = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iTransitionType = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iTransitionRate = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iTransitionValueType = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iTransitionValue = (int)TokenNumber;

					Token = (SMDToken)GetToken();
					iDelayTime = (int)TokenNumber;

					if ( iAutomataNumber < 0 || iAutomataNumber >= MAX_MONSTER_AI_AUTOMATA )
					{
						CLog.MsgBox("[Monster AI Automata] - AutomataNumber(%d) Error (%s) File. ",iAutomataNumber, lpszFileName);
						continue;
					}

					if ( iCurrentState < 0 || iCurrentState >= MAX_AI_STATE )
					{
						CLog.MsgBox("[Monster AI Automata] - CurrentState(%d) Error (%s) File. ",iCurrentState, lpszFileName);
						continue;
					}

					if ( iNextState < 0 || iNextState >= MAX_AI_STATE )
					{
						CLog.MsgBox("[Monster AI Automata] - NextState(%d) Error (%s) File. ",iNextState, lpszFileName);
						continue;
					}

					if ( iPriority < 0 || iPriority >= MAX_AI_PRIORITY )
					{
						CLog.MsgBox("[Monster AI Automata] - Priority(%d) Error (%s) File. ",iPriority, lpszFileName);
						continue;
					}


					TMonsterAIState * AIState = &TMonsterAIAutomata::s_MonsterAIAutomataArray[iAutomataNumber].m_AIState[iCurrentState][iPriority];

					AIState->m_iPriority = iPriority;
					AIState->m_iCurrentState = iCurrentState;
					AIState->m_iNextState = iNextState;
					AIState->m_iTransitionType = iTransitionType;
					AIState->m_iTransitionRate = iTransitionRate;
					AIState->m_iTransitionValueType = iTransitionValueType;
					AIState->m_iTransitionValue = iTransitionValue;
					AIState->m_iDelayTime = iDelayTime;

					memcpy(AIState->m_szStateTransitionDesc, szStateTransitionDesc, sizeof(szStateTransitionDesc));

					CLog.LogAddC(TColor.Red(),"[Monster AI Automata] Loaded Transition Desc . [ %s ]", AIState->m_szStateTransitionDesc);

					TMonsterAIAutomata::s_MonsterAIAutomataArray[iAutomataNumber].m_iAutomataNumber = iAutomataNumber;
					TMonsterAIAutomata::s_MonsterAIAutomataArray[iAutomataNumber].m_AIStateTransCount[iCurrentState]++;
				}
			}
		
		}

		fclose(SMDFile);
		CLog.LogAddC(TColor.Red(),"[Monster AI Automata] - %s file is Loaded", lpszFileName);
		TMonsterAIAutomata::s_bDataLoad = TRUE;
	}
	catch(DWORD)
	{
		CLog.MsgBox("[Monster AI Automata] - Loading Exception Error (%s) File. ", lpszFileName);
	}

	return FALSE;
}





BOOL TMonsterAIAutomata::DelAllAutomata()
{
	for ( int i =0;i<MAX_MONSTER_AI_AUTOMATA;i++)
	{
		TMonsterAIAutomata::s_MonsterAIAutomataArray[i].Reset();
	}

	return FALSE;
}


TMonsterAIAutomata * TMonsterAIAutomata::FindAutomata(int iAutomataNumber)
{
	if ( iAutomataNumber < 0 || iAutomataNumber >= MAX_MONSTER_AI_AUTOMATA )
	{
		CLog.LogAdd("[Monster AI Automata] FindAutomata() Error - (AutomataNumber=%d) ", iAutomataNumber);
		return NULL;
	}

	if ( TMonsterAIAutomata::s_MonsterAIAutomataArray[iAutomataNumber].m_iAutomataNumber == iAutomataNumber )
	{
		return &TMonsterAIAutomata::s_MonsterAIAutomataArray[iAutomataNumber];
	}
	
	CLog.LogAdd("[Monster AI Automata] FindAutomata() Error - (AutomataNumber=%d) ", iAutomataNumber);

	return NULL;
}



TMonsterAIState * TMonsterAIAutomata::RunAutomata(int iIndex)
{
	LPOBJ lpObj = &gObj[iIndex];

	if ( MAX_AI_STATE_RANGE(lpObj->m_iCurrentAIState) == FALSE )
		return NULL;

	LPOBJ lpTargetObj = NULL;
	int iMaxAgro = -1;

	int iTargetIndex = lpObj->m_Agro.GetMaxAgroUserIndex(lpObj->m_Index);

	// Search The user with Max Agro to make its enemy
	if ( iTargetIndex != -1 )
	{
		lpTargetObj = &gObj[iTargetIndex];

		if ( MONSTER_UTIL.FindMonViewportObj(lpObj->m_Index, lpTargetObj->m_Index) )
		{
			iMaxAgro = lpObj->m_Agro.GetAgro(iTargetIndex);
			lpObj->TargetNumber = iTargetIndex;
		}
		else
		{
			lpObj->TargetNumber = -1;
			lpTargetObj = NULL;
		}
	}

	BOOL bRateSuccess = FALSE;

	int iCurrentState = lpObj->m_iCurrentAIState;
	int iMaxStateTransCount = this->m_AIStateTransCount[iCurrentState];

	for ( int iPriority=0;iPriority<iMaxStateTransCount;iPriority++)
	{
		TMonsterAIState * AIState = &this->m_AIState[iCurrentState][iPriority];
		BOOL bTransition = FALSE;	// If there is an apropiate Value it is set to TRUE

		// Choose the right action according Transation Type 
		switch ( AIState->m_iTransitionType )
		{
			case MAI_STATE_TRANS_NO_ENEMY:
				if ( lpTargetObj == NULL )
				{
					bTransition = TRUE;
				}
				break;

			case MAI_STATE_TRANS_IN_ENEMY:
				if ( lpTargetObj )
				{
					if ( gObjCalDistance(lpObj, lpTargetObj) <= lpObj->m_AttackRange )
					{
						bTransition = TRUE;
					}
				}
				break;

			case MAI_STATE_TRANS_OUT_ENEMY:
				if ( lpTargetObj )
				{
					if ( gObjCalDistance(lpObj, lpTargetObj) > lpObj->m_AttackRange )
					{
						bTransition =  TRUE;
					}
				}
				break;

			//case MAI_STATE_TRANS_DIE_ENEMY:

			case MAI_STATE_TRANS_DEC_HP:
				if ( AIState->m_iTransitionValue > lpObj->Life )
				{
					bTransition = TRUE;
				}
				break;

			case MAI_STATE_TRANS_IMMEDIATELY:
				bTransition = TRUE;
				break;

			case MAI_STATE_TRANS_DEC_HP_PER:
				{
					AIState->m_iTransitionValue = (AIState->m_iTransitionValue > 0)? AIState->m_iTransitionValue : 0;
					AIState->m_iTransitionValue = (AIState->m_iTransitionValue < 100 )? AIState->m_iTransitionValue : 100 ;
					int iLife = (int)(((float)lpObj->AddLife + lpObj->MaxLife) * (float)AIState->m_iTransitionValue / 100.0f);

					if ( iLife > lpObj->Life )
					{
						bTransition = TRUE;
					}
				}
				break;

			case MAI_STATE_TRANS_AGRO_UP:
				if ( lpTargetObj )
				{
					if ( iMaxAgro >= AIState->m_iTransitionValue )
					{
						bTransition = TRUE;
					}
				}
				break;

			case MAI_STATE_TRANS_AGRO_DOWN:
				if ( lpTargetObj )
				{
					if ( iMaxAgro <= AIState->m_iTransitionValue )
					{
						bTransition = TRUE;
					}
				}
				break;

			case MAI_STATE_TRANS_GROUP_SOMMON:
				if ( lpObj->m_iGroupNumber )
				{
					if ( TMonsterAIGroup::FindGroupMemberToSommon(lpObj->m_Index, lpObj->m_iGroupNumber, lpObj->m_iGroupMemberGuid) )
					{
						bTransition = TRUE;
					}
				}
				// break;	// #error Apply Deathway fix here

			case MAI_STATE_TRANS_GROUP_HEAL:
				if ( lpObj->m_iGroupNumber )
				{
					if ( TMonsterAIGroup::FindGroupMemberToHeal(lpObj->m_Index, lpObj->m_iGroupNumber, lpObj->m_iGroupMemberGuid, 5) )
					{
						bTransition = TRUE;
					}
				}
				break;
		}

		// If is Wrong State
		if ( bTransition == FALSE )	
			continue;

		if ( (rand()%100) < AIState->m_iTransitionRate )
		{
			bRateSuccess = TRUE;
			lpObj->m_iLastAutomataDelay = AIState->m_iDelayTime;
			return &this->m_AIState[iCurrentState][iPriority];
		}
	}

	return NULL;
}