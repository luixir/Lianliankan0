#include "StdAfx.h"
#include "GameLogic.h"
#include <random>


CGameLogic::CGameLogic(void)
{
	m_nVexNum = 0;
}

CGameLogic::~CGameLogic(void)
{
}

void CGameLogic::InitMap(int anMap[][4])
{
	int temp[4][4] = {2, 0, 1, 3, 2, 2, 1, 3, 2, 1, 0, 0, 1, 3, 0, 3};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			anMap[i][j] = temp[i][j];
		}
	}
}

bool CGameLogic::IsLink(int anMap[][4], Vertex v1, Vertex v2)
{
	PushVertex(v1);
	if ((anMap[v1.row][v1.col] == anMap[v2.row][v2.col]))
	{
		if (v1.row == v2.row)
		{
			if (LinkInRow(anMap, v1, v2))
			{	
				PushVertex(v2);
				return true;
			}
		}
		else if (v1.col == v2.col)
		{
			if (LinkInCol(anMap, v1, v2))
			{
				PushVertex(v2);
				return true;
			}
		}
		
		if (OneCornerLink(anMap, v1, v2))
		{
			PushVertex(v2);
			return true;
		}

		if (TwoCornerLink(anMap, v1, v2))
		{
			PushVertex(v2);
			return true;
		}
	}

	PopVertex();
	return false;
}

void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}

void CGameLogic::PushVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
	CString str;
	str.Format(_T("IN %d"), m_nVexNum);
	AfxMessageBox(str);
}

void CGameLogic::PopVertex()
{
	m_nVexNum--;
	CString str;
	str.Format(_T("OUT %d"), m_nVexNum);
	AfxMessageBox(str);
}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

void CGameLogic::Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

Vertex CGameLogic::CreateVertex(int nRow, int nCol)
{
	Vertex v;
	v.row = nRow;
	v.col = nCol;
	return v;
}

bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow = v1.row;

	//ensure nCol1 value less then nCol2
	if (nCol1 > nCol2)
	{
		Swap(nCol1,nCol2);
	}
	// link is straight line
	for (int i = nCol1 + 1; i < nCol2; i++)
	{
		if (anMap[nRow][i] != BLANK)
		{	
			return false;
		}
	}
	return true;
}

bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol = v1.col;

	//ensure nCol1 value less then nCol2
	if (nRow1 > nRow2)
	{
		Swap(nRow1,nRow2);
	}
	// link is straight line
	for (int i = nRow1 + 1; i < nRow2; i++)
	{
		if (anMap[i][nCol] != BLANK)
		{	
			return false;
		}
	}
	return true;
}

bool CGameLogic::LineX(int anMap[][4], int nRow, int nCol1, int nCol2)
{
	if(nCol1 > nCol2)
	{
		Swap(nCol1,nCol2);
	}
	for(int nCol = nCol1; nCol <= nCol2; nCol++)
	{
		if(anMap[nRow][nCol] != BLANK)
		{	
			return false;
			break;
		}
	}
	return true;
}

bool CGameLogic::LineY(int anMap[][4], int nRow1, int nRow2, int nCol)
{
	if(nRow1 > nRow2)
	{
		Swap(nRow1,nRow2);
	}
	for(int nRow = nRow1; nRow <= nRow2; nRow++)
	{
		if(anMap[nRow][nCol] != BLANK)
		{	
			return false;
			break;
		}
	}
	return true;
}

bool CGameLogic::OneCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;

	if(nRow1 > nRow2)
	{
		Swap(nRow1,nRow2);
		Swap(nCol1,nCol2);
	}
	if(nCol2 < nCol1)
	{
		if(LineY(anMap, nRow1+1, nRow2, nCol1) && LineX(anMap,nRow2, nCol1, nCol2+1))
		{
			//PushVertex(v1);
			PushVertex(CreateVertex(nRow2,nCol1));
			return true;
		}
		if(LineY(anMap, nRow2-1, nRow1, nCol2) && LineX(anMap, nRow1,nCol2, nCol1-1))
		{			
			//PushVertex(v1);
			PushVertex(CreateVertex(nRow1, nCol2));
			return true;
		}
	}
	else
	{
		if(LineY(anMap, nRow1+1, nRow2, nCol1) && LineX(anMap,nRow2, nCol1, nCol2-1))
		{
			//PushVertex(v1);
			PushVertex(CreateVertex(nRow2, nCol1));
			return true;
		}
		if(LineY(anMap, nRow2-1, nRow1, nCol2) && LineX(anMap, nRow1, nCol2, nCol1+1))
		{
			//PushVertex(v1);
			PushVertex(CreateVertex(nRow1, nCol2));
			return true;
		}
	}
	//PopVertex();
	return false;
}

bool CGameLogic::TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	for (int i = v1.col - 1; i >= 0; i--)
	{
		PushVertex(CreateVertex(v1.row, i));
		if (anMap[v1.row][i] != BLANK)
		{
			break;
		}
		else if (OneCornerLink(anMap, CreateVertex(v1.row, i), v2))
		{
			//PushVertex(CreateVertex(v1.row, i));
			return true;
		}
		PopVertex();
	}
	PopVertex();

	for (int i = v1.col + 1; i < 4; i++)
	{
		PushVertex(CreateVertex(v1.row, i));
		if (anMap[v1.row][i] != BLANK)
		{
			break;
		}
		else if (OneCornerLink(anMap, CreateVertex(v1.row, i), v2))
		{
			//PushVertex(CreateVertex(v1.row, i));
			return true;
		}
		PopVertex();
	}
	PopVertex();

	for (int i=v1.row-1; i >= 0; i--)
	{
		PushVertex(CreateVertex(i, v1.col));
		if (anMap[i][v1.col] != BLANK)
		{
			break;
		}
		else if (OneCornerLink(anMap, CreateVertex(i, v1.col), v2))
		{	
			//PushVertex(CreateVertex(i, v1.col));
			return true;
		}
		PopVertex();
	}
	PopVertex();

	for (int i = v1.row + 1; i < 4; i++)
	{
		PushVertex(CreateVertex(i, v1.col));
		if (anMap[i][v1.col] != BLANK)
		{
			break;
		}
		else if (OneCornerLink(anMap, CreateVertex(i, v1.col), v2))
		{
			//PushVertex(CreateVertex(i, v1.col));
			return true;
		}
		PopVertex();
	}
	PopVertex();

	return false;
}