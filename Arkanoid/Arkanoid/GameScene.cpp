#include "GameScene.h"
#include "SceneMng.h"

GameScene::GameScene()
{
	Init();
}

void GameScene::Register()
{
	nextScene = eGameScene::NONE;
}

void GameScene::Enter()
{
	ingame = new Ingame(g_hWnd);
	ingame->Init();
}

void GameScene::Exit()
{

}

void GameScene::Rander(HDC hdc)
{
	ingame->Rander(hdc);
}

void GameScene::Update(float frametime)
{
	float test=10;
	ingame->Update(test, frametime);
	if (ingame->GameOver())
	{
		nextScene = eGameScene::DEFEAT;
		SceneMng::GetInstance(g_hWnd)->ScnMove(nextScene);
	}
		
}

LRESULT CALLBACK GameScene::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		ingame->Input(wParam);
		//g_Keystate = true;
		break;
	case WM_KEYUP:
		if (wParam == VK_LEFT || wParam == VK_RIGHT)
			ingame->KeyState(false);
		break;
	}
	return FALSE;
}
