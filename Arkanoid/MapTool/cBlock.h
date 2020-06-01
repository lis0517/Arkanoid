#pragma once

//enum BlockType { IMMORTAL, NOMALBLOCK, UNIQUEBLOCK};
enum BlockStyle {
	RECTANGLE
};

class cBlock
{
	Vector2 _pos;//위치
	Vector2 _size;//크기
	HPEN _pen, oldPen;//펜 구조체
	HBRUSH _brush, oldBrush;//브러쉬 구조체
	RECT m_Rect;//사각형
		
	int m_Blockstyle;//블럭의 스타일
	int m_Blocktype;//블럭의 타입
	int m_BlockColor;
public:
	cBlock();
	~cBlock();
	//////////////SetFunc//////////////
public:
	void SetPen(HDC hdc, int penStyle, int width, DWORD color);
	void SetBrush(HDC hdc, DWORD color);
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
	eItem_List GetItemList();
	Vector2 Getpos();
	Vector2 Getsize();
	RECT GetRect();
};

class BlockMng : public Singleton<BlockMng>
{
private:
	std::vector<cBlock*> _block;

public:
	BlockMng();
	~BlockMng();

	void Init();

};