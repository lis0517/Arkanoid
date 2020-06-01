#pragma once

class cMap
{
	std::vector<cBlock*> m_Wall;
	std::vector<cBlock*> m_NomalBlock;
	std::vector<cBlock*> m_UniqueBlock;

	HDC _hdc;
	RECT rect;
public:
	cMap();
	~cMap();

public:
	void Init();
	void Render(HDC hdc);

	std::vector<cBlock*> GetWall() { return m_Wall; }
	std::vector<cBlock*> GetNomal() { return m_NomalBlock; }
	std::vector<cBlock*> GetUnique() { return m_UniqueBlock; }
};

