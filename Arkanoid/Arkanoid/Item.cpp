#include "Item.h"
#include "Block.h"
#include "OutPut.h"
#include "Ingame.h"

typedef bool (Item::*ItemCall)(bool state);
typedef map<int, ItemCall>::iterator MITER;
map<int, ItemCall> mapitem;

Item::Item(HWND hWnd) 
{
	m_itemlist = eItem_List::NONEITEM;
	Init();
}

Item::~Item()
{
}

void Item::Init()
{
	//Nomal Items
	mapitem[eItem_List::EXPANDVAUS] = &Item::ExpandVaus;
	mapitem[eItem_List::SHRINKVAUS] = &Item::ShrinkVaus;
	mapitem[eItem_List::SLOWBALL] = &Item::SlowBall;
	//mapitem[eItem_List::GRAPBALL] = &Item::GrapBall;
	//mapitem[eItem_List::INCREASEBALL] = &Item::IncreaseBall;
	//Unique Items
	//mapitem[eItem_List::MEGABALL] = &Item::MegaBall;
	mapitem[eItem_List::EXTRALIFE] = &Item::ExtraLife;
	//mapitem[eItem_List::LASER] = &Item::LaserVaus;
	//mapitem[eItem_List::STAGESKIP] = &Item::StageSkip;
}

void Item::Nomalstate(Block* vaus)
{
	nVaus = vaus;
	//m_state = state;
}

void Item::StateUpdate(bool state)
{
	m_state = state;
}


void Item::ItemCall()
{
	MITER iter = mapitem.find(m_itemlist);
	if (iter != mapitem.end())
	{
		(this->*mapitem[m_itemlist])(m_state);
	}
}

bool Item::SlowBall(bool activateItem)
{
	float speed = OutPut::GetSpeed();
	speed = speed / 1.5f;
	OutPut::SetSpeed(speed);
	return true;
}

//Vector2 Item::SlowBall(Block * ball, bool activateItem)
//{
//	Vector2 temp;
//	
//	/*temp.x = speedx / 1.5;
//	temp.y = speedy / 1.5;*/
//
//	return temp;
//}

//바우스 길이 늘어남
//타겟 블럭 포인터를 받아오고 아이템이 활성화 된 상태인지 
//확인하기 위해 bool 변수를 받아온다. 
bool Item::ExpandVaus(bool activateItem)
{
	//if (activateItem == true)
	//{
	//	
	//	//return;
	//}
	Vector2 temp = nVaus->Getsize();
	float m_calx = temp.x * 1.5;
	float m_caly = temp.y;
	nVaus->SetSize(m_calx, m_caly);
	return true;
}

bool Item::ShrinkVaus(bool activateItem)
{
	/*if (activateItem == true)
	{
	
	}*/
	Vector2 temp = nVaus->Getsize();
	float m_calx = temp.x / 1.5;
	float m_caly = temp.y;
	nVaus->SetSize(m_calx, m_caly);
	return true;
}

bool Item::GrapBall(bool activateItem)
{

	return false;
}

bool Item::IncreaseBall(bool activateItem)
{
	return false;
}

bool Item::LaserVaus(bool activateItem)
{
	return false;
}

bool Item::ExtraLife(bool activateItem)
{
	int life = Ingame::GetLife();
	life++;
	Ingame::SetLife(life);
	return true;
}

bool Item::MegaBall(bool activateItem)
{

	return false;
}

bool Item::StageSkip(bool activateItem)
{
	return false;
}




