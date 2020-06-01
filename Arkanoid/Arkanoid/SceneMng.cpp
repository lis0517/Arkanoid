#include "SceneMng.h"

typedef std::map<BaseScene::eGameScene, BaseScene*> MITER;

SceneMng::SceneMng(HWND hWnd)
{
	if (sceneList.size() == 0) 
	{
		g_hWnd = hWnd;
		currScene = BaseScene::eGameScene::NONE;
		RegisterScene();
	}
}

void SceneMng::RegisterScene()
{
	sceneList[BaseScene::eGameScene::LOGO] = new LogoScene();
	sceneList[BaseScene::eGameScene::TITLE] = new TitleScene();
	sceneList[BaseScene::eGameScene::INGAME] = new GameScene();
	sceneList[BaseScene::eGameScene::DEFEAT] = new DefeatScene();

	currScene = BaseScene::eGameScene::LOGO;
}

void SceneMng::EnableScn(BaseScene::eGameScene scene)
{
	currScene = scene;
	sceneList[currScene]->Enter();
}

void SceneMng::ScnMove(BaseScene::eGameScene scene)
{
	BaseScene::eGameScene prevScene = currScene;
	currScene = sceneList[currScene]->GetScene();
	sceneList[prevScene]->Exit();
	EnableScn(currScene);
}

void SceneMng::Update(float delta)
{
	sceneList[currScene]->Update(delta);
}

void SceneMng::Render(HDC hdc)
{
	sceneList[currScene]->Rander(hdc);
}

void SceneMng::EventScn(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	sceneList[currScene]->MsgProc(hWnd, msg, wParam, lParam);
}

