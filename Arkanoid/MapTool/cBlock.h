#pragma once

//enum BlockType { IMMORTAL, NOMALBLOCK, UNIQUEBLOCK};
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
		
	int m_Blockstyle;//���� ��Ÿ��
	int m_Blocktype;//���� Ÿ��
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