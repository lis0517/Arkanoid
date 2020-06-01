#pragma once
#define SMT MapTool::GetInstance()

class MapTool : public Singleton<MapTool>
{
private:
	ImageMng	_ImageMng;
	DlgControl	_DlgControl;
	DlgBlock	_DlgBlock;
	

	int m_BlockWidth;
	int m_BlockHeight;
	int m_size;
	int m_Cellsize;
public:
	MapTool();
	~MapTool();

public:
	void SetControlBlock();
	int GetBlockWidth(); //{ return m_BlockWidth; }
	int GetBlockHeigth(); //{ return m_BlockHeight; }
	int GetSize();
public:
	void Init();
	void Update();
	void Render();
};

#define SMT MapTool::GetInstance()
