#pragma once
#include "global.h"
class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	void InitMap(int anMap[][4]);
	bool IsLink(int anMap[][4], Vertex v1, Vertex v2);
	void Clear(int anMap[][4], Vertex v1, Vertex v2);
	int GetVexPath(Vertex avPath[4]);
	bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);
	bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);
	bool OneCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	bool TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2);
	bool LineY(int anMap[][4], int nRow1, int nRow2, int nCol);
	bool LineX(int anMap[][4], int nRow, int nCol1, int nCol2);

protected:
	void PushVertex(Vertex v);
	void PopVertex();
	void Swap(int &a, int &b);
	Vertex CreateVertex(int nRow, int nCol);

	Vertex m_avPath[4];
	int m_nVexNum;

};

