#include "BaseScene.h"
#include "SceneMng.h"

//std::map<eChannel, eGameScene> * scenelist = new std::map<eChannel, eGameScene>;

BaseScene::BaseScene()
{
	Init();
}

//LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch(msg)
//	{
//	}s
//}

void BaseScene::Init()
{
	Register();
}



