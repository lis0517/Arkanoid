#pragma once

#define WIDTH		900
#define HEIGHT		800
#define PREVWIDTH	600
#define MAKEFUNC(TYPE,NAME)\
private: TYPE m_##NAME;\
public: TYPE Get##NAME(){return m_##NAME;}\
void Set##NAME(TYPE value){m_##NAME = value;}

enum eBlockType
{
	NONE,
	IMMORTAL,
	NOMALBLOCK,
	UNIQUEBLOCK,
};

enum eBlock_List
{
	WHITE,
	ORANGE,
	BLUEGREEN,
	GREEN,
	RED,
	PURPLE,
	YELLOW,
	BLUE,

	SILVER,
	GOLD,
	FORTRESS,
};

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