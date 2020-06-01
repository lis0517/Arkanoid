#pragma once

#include <map>
#include <iterator>
#include "TSingleton.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "DefeatScene.h"
#include "BaseScene.h"


//enum eGameScene
//{
//	NONE, LOGO, TITLE, INGAME, LOSE, VICTORY,
//};
//
//enum eChannel
//{
//	C1, C2
//};

class SceneMng : public TSingleton<SceneMng>
{
	//friend class TSingleton<SceneMng>;
protected:
	std::map<BaseScene::eGameScene, BaseScene*> sceneList;
public:
	HWND _hWnd;
	SceneMng(HWND hWnd);
public:
	BaseScene::eGameScene currScene = BaseScene::eGameScene::NONE;

	void RegisterScene();
	
	void EnableScn(BaseScene::eGameScene scene);
	void ScnMove(BaseScene::eGameScene scene);
	//BaseScene GetScene(eGameScene);
	void Update(float delta);
	void Render(HDC hdc);
	void EventScn(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

