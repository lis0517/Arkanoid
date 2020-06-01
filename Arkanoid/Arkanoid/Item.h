#pragma once
#include <Windows.h>
#include <map>
//#include "Block.h"
#include "vector2.h"
#include "Util.h"
using namespace std;

enum eItem_List
{
	NONEITEM,

	EXTRALIFE,// ��� 1�� �߰�
	EXPANDVAUS,// �ٿ콺 ũ�� ����
	SHRINKVAUS,// �ٿ콺 ũ�� ����
	REVERSEVAUS,// �ٿ콺 ������ ����
	LASER,//�ٿ콺 ������
	SKIPSTAGE,//�������� �Ѿ��

	GRAPBALL,//�� ���
	SLOWBALL, //�� �ӵ� ����
	INCREASEBALL, // �� ���� ���� (3��)
	MEGABALL,// �ް� ��(������ ����)
};

class Block;
class OutPut;
class Ingame;
class Item 
{
private:
	//eItem_List m_itemlist;
	Block * nVaus;
	Block * nBall;
	bool m_state;
public:
	Item(HWND hWnd);
	~Item();
	void Init();
	void Nomalstate(Block * vaus);
	void StateUpdate(bool activateItem);
	void ItemCall();
	bool SlowBall(bool activateItem);
	bool ExpandVaus(bool activateItem);
	bool ShrinkVaus(bool activateItem);
	bool GrapBall(bool activateItem);
	bool IncreaseBall(bool activateItem);
	
	bool LaserVaus(bool activateItem);
	bool ExtraLife(bool activateItem);
	bool MegaBall(bool activateItem);
	bool StageSkip(bool activateItem);
	MAKEFUNC(eItem_List, itemlist)
};

