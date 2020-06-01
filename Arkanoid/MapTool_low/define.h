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

	EXTRALIFE,// 목숨 1개 추가
	EXPANDVAUS,// 바우스 크기 증가
	SHRINKVAUS,// 바우스 크기 감소
	REVERSEVAUS,// 바우스 움직임 반전
	LASER,//바우스 레이저
	SKIPSTAGE,//스테이지 넘어가기

	GRAPBALL,//공 잡기
	SLOWBALL, //공 속도 감소
	INCREASEBALL, // 공 개수 증가 (3개)
	MEGABALL,// 메가 볼(데미지 증가)
};