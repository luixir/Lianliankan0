#include "StdAfx.h"
#include "GameControl.h"


CGameControl::CGameControl(void)
{
}

CGameControl::~CGameControl(void)
{
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}


void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
}


void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}


bool CGameControl::Link(Vertex avPath[4], int &nVexNum)
{
	
	if (!((m_svSelFst.row == m_svSelSec.row) && (m_svSelFst.col == m_svSelSec.col)))
	{
		CGameLogic m_logic;
		if (m_logic.IsLink(m_anMap, m_svSelFst, m_svSelSec))
		{

			m_logic.Clear(m_anMap, m_svSelFst, m_svSelSec);	// remove element
			nVexNum = m_logic.GetVexPath(avPath);				// return vertex path

			return true;
		}
	}
	return false;
}


void CGameControl::StartGame(void)
{
	logic.InitMap(m_anMap);
}
