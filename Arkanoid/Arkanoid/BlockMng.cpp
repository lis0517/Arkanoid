#include "BlockMng.h"

BlockMng::BlockMng(HWND hWnd)
{
	GetClientRect(hWnd, &rect);
	this->hWnd = hWnd;
 	x = rect.right / 2;
	y = rect.bottom / 5 * 4;
	m_Ballsize = 1;
	m_degree = 45.0f;
	//m_degree = 135.0f;
}

BlockMng::~BlockMng(){}

void BlockMng::Wall(HDC hdc)
{	
	Vector2 vec;
	DWORD Brgb = RGB(192, 192, 192);
	DWORD Lrgb = RGB(96, 96, 96);
	for (int i = 0; i < 3; i++) {
		Block * nWall = new Block(hWnd);
		nWall->SetBlockStyle(BlockStyle::RECTANGLE);
		nWall->SetPen(PS_SOLID,2,Lrgb);
		nWall->SetBrush(Brgb);
		switch (i)
		{
		case 0://À§
			nWall->SetPos((float)(rect.left+rect.right)/2, (float)rect.top);
			nWall->SetSize((float)rect.right, 20);
			nWall->SetDirection(vec.bottom);
			break;
		case 1://¿Þ
			nWall->SetPos((float)0, (float)HEIGHT / 2);
			nWall->SetSize(20, (float)HEIGHT);
			nWall->SetDirection(vec.right);
			break;
		case 2://¿À¸¥
			nWall->SetPos((float)WIDTH, (float)HEIGHT / 2);
			nWall->SetSize(20, (float)HEIGHT);
			nWall->SetDirection(vec.left);
			break;
		}
		m_Wall.push_back(nWall);
	}
}

void BlockMng::Ball(HDC hdc)
{
	Vector2 vec;

	DWORD pbrgb = RGB(0, 208, 208);
	DWORD plrgb = RGB(5, 120, 155);
	for (int i = 0; i < m_Ballsize; i++)
	{
		vec = { cos(PI / (180.0f / m_degree)), -sin(PI / (180.0f / m_degree)) };
		Block * ball = new Block(hWnd);
		ball->SetBlockStyle(BlockStyle::ELLIPSE);
		ball->SetPen(PS_SOLID, 1, plrgb);
		ball->SetBrush(pbrgb);
		ball->SetPos(x, y-15);
		ball->SetSize(10, 10);
		ball->SetDirection(vec);
		m_Ball.push_front(ball);
		//m_degree += 45;
	}
}

void BlockMng::Player(HDC hdc)
{
	Vector2 vec;
	DWORD pbrgb = RGB(105, 105, 105);
	DWORD plrgb = RGB(255, 10, 55);
	m_Vaus = new Block(hWnd);
	m_Vaus->SetBlockStyle(BlockStyle::RECTANGLE);
	m_Vaus->SetBlockType(BlockType::VAUS);
	m_Vaus->SetPen(PS_SOLID, 2, plrgb);
	m_Vaus->SetBrush(pbrgb);
	m_Vaus->SetPos(x, y);
	m_Vaus->SetSize(100, 20);
	m_Vaus->SetDirection(vec.top);

	m_OrignVaus = new Block(hWnd);
	//m_OrignVaus->SetBlockStyle(BlockStyle::RECTANGLE);
	//m_OrignVaus->SetBlockType(BlockType::VAUS);
	//m_OrignVaus->SetPen(hdc, PS_SOLID, 2, plrgb);
	//m_OrignVaus->SetBrush(hdc, pbrgb);
	//m_OrignVaus->SetPos(x, y);
	//m_OrignVaus->SetSize(100, 20);
	//m_OrignVaus->SetDirection(vec.top);
	*m_OrignVaus = *m_Vaus;
}

void BlockMng::DistroyBlock(HDC hdc)
{
	FILE *fp1, *fp2;

	_tfopen_s(
		&fp1
		, TEXT("Size.txt")
		//, TEXT("C:/Size.txt")
		, TEXT("r"));

	_tfopen_s(
		&fp2
		, TEXT("Block.txt")
		, TEXT("rt, ccs=UTF-8"));

	if (!fp1 || !fp2)
	{
		return;
	}

	int dataLen = 0;
	fscanf_s(fp1, "%d", &dataLen);

	DataInfo *Info = new DataInfo[dataLen];
	int dataSize = sizeof(DataInfo);
	int readCount = fread(Info, dataSize, dataLen, fp2);

	for (int i = 0; i < dataLen; ++i) {
		Block *brick = new Block(hWnd);
		brick->SetPos(Info[i]._pos.x, Info[i]._pos.y);
		brick->SetSize(Info[i]._size.x, Info[i]._size.y);
		brick->SetBrush(Info[i]._brush);
		brick->SetPen(PS_SOLID, 1, Info[i]._pen);
		brick->SetBlockType(Info[i]._type);
		brick->SetItemList(Info[i]._itemList);
		brick->SetBlockStyle(BlockStyle::RECTANGLE);

		m_Blocks.push_front(brick);
	}
}

void BlockMng::ItemBlock(Block * block, HDC hdc)
{
	if ((m_Blocks.size() == 0) || (block->GetItemList() == eItem_List::NONEITEM))
		return;
	Vector2 vec;
	float blockX = block->Getpos().x;
	float blockY = block->Getpos().y;
	float sizex = block->Getsize().x;
	float sizey = block->Getsize().y;
	eItem_List list = block->GetItemList();
	
	Block * nItemBlock = new Block(hWnd);
	nItemBlock->SetBlockStyle(BlockStyle::RECTANGLE);
	nItemBlock->SetBlockType(BlockType::ITEM);
	nItemBlock->SetPos(blockX, blockY);
	nItemBlock->SetSize(sizex/2, sizey);
	nItemBlock->SetDirection(vec.bottom);
	switch (list)
	{
	case SLOWBALL:
	{
		DWORD Brgb = RGB(255, 201, 14);
		DWORD Lrgb = RGB(0, 10, 250);
		nItemBlock->SetPen(PS_SOLID, 2, Lrgb);
		nItemBlock->SetBrush(Brgb);
		nItemBlock->SetItemList(eItem_List::SLOWBALL);
	}
	break;
	/*case INCREASEBALL:
			break;
		case MEGABALL:
			break;
		case EXTRALIFE:
			break;*/
	case EXPANDVAUS:
	{
		DWORD Brgb = RGB(28, 70, 242);
		DWORD Lrgb = RGB(140, 10, 20);
		nItemBlock->SetPen(PS_SOLID, 2, Lrgb);
		nItemBlock->SetBrush(Brgb);
		nItemBlock->SetItemList(eItem_List::EXPANDVAUS);
	}
	break;
	case SHRINKVAUS:
	{
		DWORD Brgb = RGB(129, 15, 255);
		DWORD Lrgb = RGB(140, 10, 20);
		nItemBlock->SetPen(PS_SOLID, 2, Lrgb);
		nItemBlock->SetBrush(Brgb);
		nItemBlock->SetItemList(eItem_List::SHRINKVAUS);
	}
	break;
	case EXTRALIFE:
	{
		DWORD Brgb = RGB(125, 125, 125);
		DWORD Lrgb = RGB(140, 10, 20);
		nItemBlock->SetPen(PS_SOLID, 2, Lrgb);
		nItemBlock->SetBrush(Brgb);
		nItemBlock->SetItemList(eItem_List::EXTRALIFE);
	}
	break;

	}
	m_Item.push_back(nItemBlock);
}

void BlockMng::BackToOrign()
{
	float vausSizex = m_OrignVaus->Getsize().x;
	float vausSizey = m_OrignVaus->Getsize().y;
	m_Vaus->SetSize(vausSizex, vausSizey);
}

vector<Block*>* BlockMng::GetWall()
{
	return &m_Wall;
}

vector<Block*>* BlockMng::GetItemBlock()
{
	return &m_Item;
}

list<Block*>* BlockMng::GetBall()
{
	return &m_Ball;
}

list<Block*>* BlockMng::GetDisBlock()
{
	return &m_Blocks;
}

Block * BlockMng::GetPlayer()
{
	return m_Vaus;
}




