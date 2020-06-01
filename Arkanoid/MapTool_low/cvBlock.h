#pragma once

enum BlockStyle {
	RECTANGLE
};

class cBlock
{
	Vector2 _pos;//��ġ
	Vector2 _size;//ũ��
	HPEN _pen, oldPen;//�� ����ü
	HBRUSH _brush, oldBrush;//�귯�� ����ü
	RECT m_Rect;//�簢��
	DWORD _bColor, _lColor;
	int m_Blockstyle;//���� ��Ÿ��
	eBlockType m_Blocktype;//���� Ÿ��
	eBlock_List m_BlockColor;
	int m_ItemList;
public:
	cBlock();
	~cBlock();
	//////////////SetFunc//////////////
public:
	void SetPen(int penStyle, int width, DWORD color);
	void SetBrush( DWORD color);
	void SetPos(float x, float y);
	void SetSize(float x, float y);
	void SetBlockType(eBlockType type);
	void SetBlockStyle(BlockStyle style);
	void SetBlockColor(eBlock_List color);
	void SetPosX(float x);
	void SetItemList(eItem_List item);
	//////////////DrawFunc//////////////
public:
	void DrawRectangle(HDC, int, int, int, int);
	//////////////RenderFunc//////////////
public:
	void Init();
	void Render(HDC hdc);
	void CalculateRect();
	void Release();
public:
	int GetItemList();
	Vector2 Getpos();
	Vector2 Getsize();

	RECT GetRect();
	DWORD GetbColor() { return _bColor; }
	DWORD GetlColor() { return _lColor; }
	int GetStyle() { return m_Blockstyle; }//���� ��Ÿ��
	eBlockType GetType() { return m_Blocktype; }//���� Ÿ��
	eBlock_List GetColor() { return m_BlockColor; }
};

class cMap
{
	std::vector<cBlock*> m_Wall;
	std::vector<cBlock*> m_NomalBlock;
	std::vector<cBlock*> m_UniqueBlock;
	std::vector<cBlock*> m_saveBlock;

	HDC _hdc;
	RECT rect;
public:
	cMap(HWND hWnd);
	~cMap();

public:
	void Init(HWND hWnd);
	void Render(HDC hdc);

	std::vector<cBlock*> * GetWall()   { return &m_Wall; }
	std::vector<cBlock*> * GetNomal()  { return &m_NomalBlock; }
	std::vector<cBlock*> * GetUnique() { return &m_UniqueBlock; }
	std::vector<cBlock*> * GetSave()   { return &m_saveBlock; }
};

