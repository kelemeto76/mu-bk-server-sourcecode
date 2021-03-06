//**********************************************************************//
// Project:	HaRiBO MU GameServer - Season 4								//
// Company: RealCoderZ MU Development � 2010							//
// Description: MU CLogin Count Structures & Functions					//
// Decompilation By: Deathway											//
// Coded & Modified By:	WolF & M.E.S									//
//**********************************************************************//
#include "../Header Files/stdafx.h"
#include "../Header Files/CLoginCount.h"



CLoginCount::CLoginCount()
{
	this->Init();
}

CLoginCount::~CLoginCount()
{
	return;
}

void CLoginCount::Init()
{
	this->m_count=0;
}

void CLoginCount::Add()
{
	this->m_count++;
}

void CLoginCount::Delete()
{
	this->m_count--;

	if ( this->m_count < 0 )
	{
		this->m_count = 0;
	}
}

int CLoginCount::Get()
{
	return this->m_count;
}

