#pragma once
#include "global.h"
#include "GameLogic.h"
class CGameControl
{
public:
	CGameControl(void);
	~CGameControl(void);
	
protected:
	int m_anMap[4][4];
	Vertex m_svSelFst;
	Vertex m_svSelSec;
	CGameLogic logic;
public:
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[4], int &nVexNum);

	void StartGame(void);
};

