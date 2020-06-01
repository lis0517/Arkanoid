#include "OutPut.h"

typedef list<Block*>::iterator LITER;
typedef vector<Block*>::iterator VITER;

static float ballSpeed = 250.0f;

OutPut::OutPut(HWND hWnd)
{
	Init(hWnd);
}

OutPut::~OutPut(){}

void OutPut::Init(HWND hWnd)
{
	m_x = 0.0f;
	m_y = 0.0f;
	x = 0;
	y = 0;
	bx = 0.0f;
	by = 0.0f;
	playerSpeed = 200.0f;
	
	mng = new BlockMng(hWnd);
	flag = false;
	Ballflag = false;
	stateflag = false;
	m_Moving = false;
	m_reset = false;
}

//맵을 그린다.
void OutPut::SettingMap(HDC hdc)
{
	if (!flag) {
		this->hdc = hdc;
		mng->Wall(hdc);
		mng->Player(hdc);
		mng->DistroyBlock(hdc);
		mng->Ball(hdc);
		flag = true;
	}
}

bool OutPut::ResetMap(HDC hdc)
{
	VITER iter = mng->GetItemBlock()->begin();
	if (m_reset) {
		mng->GetBall()->clear();
		mng->SetBallsize(1);
		mng->GetPlayer()->SetPos(292.0f, 608.0f);
		mng->GetPlayer()->SetSize(100, 20);
		mng->Ball(hdc);
		m_reset = false;
		Ballflag = false;
		ballSpeed = 250.0f;
		for (iter; iter != mng->GetItemBlock()->end();)
		{
			if(m_reset == false){
				(*iter)->Release();
				delete (*iter);
				iter = mng->GetItemBlock()->erase(iter);
			}
			else
			{
				iter++;
			}
		}
		return true;
	}
	return false;
}

void OutPut::Render(HDC hdc)
{
	LITER it = mng->GetDisBlock()->begin();
	LITER it2 = mng->GetBall()->begin();

	for (int i=0; i < mng->GetWall()->size(); ++i)
	{
		mng->GetWall()->at(i)->Render(hdc);
	}
	for (it; it != mng->GetDisBlock()->end(); ++it)
	{
		(*it)->Render(hdc);
	}
	for (it2; it2 != mng->GetBall()->end(); ++it2)
	{
		(*it2)->Render(hdc);
	}
	for (int i = 0; i < mng->GetItemBlock()->size(); ++i)
	{
		mng->GetItemBlock()->at(i)->Render(hdc);
	}
	mng->GetPlayer()->Render(hdc);
}

void OutPut::Release()
{
	LITER it = mng->GetDisBlock()->begin();
	LITER it2 = mng->GetBall()->begin();

	for (int i = 0; i < mng->GetWall()->size(); ++i)
	{
		mng->GetWall()->at(i)->Release();
		delete mng->GetWall()->at(i);
		mng->GetWall()->clear();
		//delete mng->GetWall();
	}
	for (it; it != mng->GetDisBlock()->end();)
	{
		if (it != mng->GetDisBlock()->end())
		{
			(*it)->Release();
			delete (*it);
			it = mng->GetDisBlock()->erase(it);
		}
		else
		{
			it++;
		}
		//mng->GetDisBlock()->clear();
	}
	for (it2; it2 != mng->GetBall()->end();)
	{
		if (it2 != mng->GetBall()->end())
		{
			(*it2)->Release();
			delete (*it2);
			it2 = mng->GetBall()->erase(it2);
		}
		else
		{
			it2++;
		}
		//mng->GetBall()->clear();
	}
	mng->GetPlayer()->Release();
	delete mng->GetPlayer();
	
}

void OutPut::Update(float accel, float delta)
{
	m_deltaTime = delta;
	m_accel = accel;
	if (m_Moving)
		PlayerUpdate();
	if (mng->GetBallsize() == 0)
	{
		m_reset = true;
	}
	ItemUpdate();
}

void OutPut::BallUpdate(float delta)
{
	LITER iter = mng->GetBall()->begin();
	if (Ballflag) 
	{	
		
		for (iter; iter != mng->GetBall()->end(); ++iter)
		{
			//BallTest((*iter));
			CollisionCheck((*iter));
			bx = (*iter)->GetDirection().x *(ballSpeed * delta);
			by = (*iter)->GetDirection().y * (ballSpeed * delta);
			(*iter)->MovebyXY(bx, by);
			CheckPlayerDie((*iter));
				//m_reset = true;
		}
	}	
}

void OutPut::KeyState(bool state)
{
	m_Moving = state;
}

void OutPut::CollisionCheck(Block * ball)
{
	LITER it2 = mng->GetDisBlock()->begin();

	for (int i = 0; i < mng->GetWall()->size(); ++i) {
		if (CheckHit(ball, mng->GetWall()->at(i)) == true)
		{
			ballSpeed += 5;
			BlockDirection(ball, mng->GetWall()->at(i));
		}
	}
	for (it2; it2 != mng->GetDisBlock()->end();)
	{
		if (CheckHit(ball, (*it2)) == true)
		{
			ballSpeed += 5;
			BlockDirection(ball, (*it2));
			//BlockDelete((*it2));
			ItemMaker((*it2));
			
			delete (*it2);
			it2 = mng->GetDisBlock()->erase(it2);
		}
		else
		{
			it2++;
		}
	}
	if (CheckHit(ball, mng->GetPlayer()) == true)
	{
		BlockDirection(ball, mng->GetPlayer());
	}
}

void OutPut::CollisionCal(Block * ball, Block * block)
{
	float dotresult = 0.0f;
	float dotresult2 = 0.0f;
	float length = 0.0f;
	Vector2 vec, vec2, ballVector, result;
	float x_direct = ball->GetDirection().x;
	float y_direct = ball->GetDirection().y;
	ballVector = { x_direct, y_direct };

	vec2 = block->GetDirection();

	//공의 방향 벡터 반전
	vec = ballVector *-1;
	
	dotresult = vec.Dot(vec2);
	
	
	float rad = 2 * dotresult;

	float testX = rad * block->GetDirection().x - vec.x;
	float testY = rad * block->GetDirection().y - vec.y;
	ballVector = { testX, testY };

	ball->SetDirection(ballVector);
}

bool OutPut::CheckPlayerDie(Block * block1)
{
	
	if (block1->Getpos().y >= 780)
	{
		block1->Release();
		int ballsize = mng->GetBallsize();
		mng->SetBallsize(--ballsize);
		return true;
	}
	return false;
}

void OutPut::returnDelta(Block * block1, Block * block2)
{
	RECT temp;
	Vector2 vec;
	float m_tempy, m_tempx, length, pen;
	float rx, ry;
	if (IntersectRect(&temp, &block1->GetRect(), &block2->GetRect()))
	{
		m_tempy = temp.bottom - temp.top;
		m_tempx = temp.right - temp.left;
		
		if (t_Linelist.bRight)
		{
			rx = block1->Getpos().x + m_tempx;
			ry = block1->Getpos().y;
		}
		else if (t_Linelist.bLeft)
		{
			rx = block1->Getpos().x - m_tempx;
			ry = block1->Getpos().y;
		}

		if (t_Linelist.bBottom)
		{
			rx = block1->Getpos().x;
			ry = block1->Getpos().y + m_tempy;
		}
			
		else if (t_Linelist.bTop)
		{
			rx = block1->Getpos().x;
			ry = block1->Getpos().y - m_tempy;
		}
		block1->SetPos(rx, ry);
	}
}

float OutPut::DistanceSqr(float x1, float y1, float x2, float y2)
{
	float	dx, dy;							 

	dx = x2 - x1;									
	dy = y2 - y1;									

	return dx * dx + dy * dy;
}

void OutPut::KeyInput(DWORD key)
{

	if (key == VK_LEFT || key == VK_RIGHT)
	{
		m_Moving = true;
		m_keyDir = key;
	}
	if (key == VK_SPACE)
	{
		Ballflag = true;
	}
}

void OutPut::PlayerUpdate()
{
	RECT temp;
	LITER iter = mng->GetBall()->begin();
	switch (m_keyDir)
	{
	case VK_LEFT:
		if (IntersectRect(&temp, &mng->GetPlayer()->GetRect(), &mng->GetWall()->at(1)->GetRect()))
		{
			m_Moving = false;
			float m_InterW = temp.right - temp.left;
			float m_InterH = temp.bottom - temp.top;
			/*float m_x = mng->GetPlayer()->Getpos().x + m_InterW;

			mng->GetPlayer()->SetPosX(m_x);
			if (Ballflag == false)
			{
				(*iter)->SetPosX(m_x);
			}
			break;*/
			SetRect(&mng->GetPlayer()->GetRect(), mng->GetPlayer()->GetRect().left + m_InterW, 0, mng->GetPlayer()->GetRect().right + m_InterW, 0);
		}
		else
		{
			float move_x = (m_deltaTime * (playerSpeed + m_accel)) * -1;
			mng->GetPlayer()->MovebyX(move_x);
			if (Ballflag == false)
			{
				(*iter)->MovebyX(move_x);
			}
		}
		break;
	case VK_RIGHT:
		if (IntersectRect(&temp, &mng->GetPlayer()->GetRect(), &mng->GetWall()->at(2)->GetRect()))
		{
			m_Moving = false;
			float m_InterW = temp.right - temp.left;
			float m_InterH = temp.bottom - temp.top;
			/*float m_x = mng->GetPlayer()->Getpos().x - m_InterW;

			mng->GetPlayer()->SetPosX(m_x);
			if (Ballflag == false)
			{
				(*iter)->SetPosX(m_x);
			}
			break;*/
			SetRect(&mng->GetPlayer()->GetRect(), mng->GetPlayer()->GetRect().left - m_InterW, 0, mng->GetPlayer()->GetRect().right - m_InterW, 0);
		}
		else
		{
			float move_x = (m_deltaTime * (playerSpeed + m_accel));
			mng->GetPlayer()->MovebyX(move_x);
			if (Ballflag == false)
			{
				(*iter)->MovebyX(move_x);
			}
		}

		break;
	}
}

int OutPut::CheckHit(Block * block1, Block * block2)
{
	int nResult = false;
	float ar = 0.0f;
	float r = 5.0f;
	/*float test1 = block1->Getpos().x;
	float test = block2->GetRect().right + r;*/

	if ((block1->Getpos().x > block2->GetRect().left - r) &&
		(block1->Getpos().x < block2->GetRect().right + r) &&
		(block1->Getpos().y > block2->GetRect().top - r) &&
		(block1->Getpos().y < block2->GetRect().bottom + r))
	{
		nResult = true;
		ar = r;
		if (block1->Getpos().x < block2->GetRect().left) {
			// 좌측상단 모서리 체크 
			if ((block1->Getpos().y < block2->GetRect().top))
			{
				if ((DistanceSqr(block2->GetRect().left, block2->GetRect().top,
					block1->Getpos().x, block1->Getpos().y) >= ar * ar)) {
					nResult = false;
				}
			}
			else {
				// 좌측하단 모서리 체크 
				if ((block1->Getpos().y >  block2->GetRect().bottom))
				{
					if ((DistanceSqr(block2->GetRect().left, block2->GetRect().bottom,
						block1->Getpos().x, block1->Getpos().y) >= ar * ar)) {
						nResult = false;
					}
				}
			}
		}
		else {
			// 오른쪽 끝 체크 
			if (block1->Getpos().x > block2->GetRect().right) {
				// 우측 상단 모서리 체크 
				if ((block1->Getpos().y < block2->GetRect().top))
				{
					if ((DistanceSqr(block2->GetRect().right, block2->GetRect().top,
						block1->Getpos().x, block1->Getpos().y) >= ar * ar)) {
						nResult = false;
					}
				}
				else {
					// 좌측 하단 모서리 체크 
					if ((block1->Getpos().y > block2->GetRect().bottom))
					{
						if ((DistanceSqr(block2->GetRect().right, block2->GetRect().bottom,
							block1->Getpos().x, block1->Getpos().y) >= ar * ar)) {
							nResult = false;
						}
					}
				}
			}
		}
	}
	return nResult;
}

void OutPut::BlockDirection(Block * block1, Block * block2)
{
	int idx = 0;
	Vector2 vec, temp;
	temp = block1->GetDirection();
	t_Linelist = myIntersectRect(block2, block1->Getpos(), block2->Getpos());
	
	if (t_Linelist.bBottom) ++idx;
	if (t_Linelist.bTop) ++idx;
	if (t_Linelist.bLeft) ++idx;
	if (t_Linelist.bRight) ++idx;

	if (idx == 2)
	{
		temp = temp * -1;
		block1->SetDirection(temp);
		CollisionCal(block1, block2);
		return;
	}
	if (t_Linelist.bLeft)
	{
		block2->SetDirection(vec.left);
		returnDelta(block1, block2);
	}
	else if (t_Linelist.bRight)
	{
		block2->SetDirection(vec.right);
		returnDelta(block1, block2);
	}
	else if (t_Linelist.bTop)
	{
		block2->SetDirection(vec.top);
		returnDelta(block1, block2);
	}
	else if (t_Linelist.bBottom)
	{
		block2->SetDirection(vec.bottom);
		returnDelta(block1, block2);
	}
	CollisionCal(block1, block2);
}

void OutPut::BlockDelete(Block * enemy)
{
	LITER iter = mng->GetBall()->begin();
	int size = mng->GetEnemysize();
	enemy->Release();
	delete enemy;
	mng->SetEnemysize(--size);
	if (size == 0)
	{
		for (iter; iter != mng->GetBall()->end(); iter++)
		{
			mng->GetBall()->erase(iter);
		}
		mng->GetBall()->clear();
	}
}

void OutPut::ItemMaker(Block * item)
{
	mng->ItemBlock(item, hdc);
	for (int i = 0; i < mng->GetItemBlock()->size(); ++i)
	{
		mng->GetItemBlock()->at(i)->GetItem()->StateUpdate(itemstate);
	}
	itemstate = true;
}

void OutPut::ItemUpdate()
{
	VITER iter;
	iter = mng->GetItemBlock()->begin();
	if (itemstate == true) {
		float speed = 100.0f;
		float move_y = speed * m_deltaTime;
		for (iter; iter != mng->GetItemBlock()->end();)
		{
			if (CheckHit((*iter), mng->GetPlayer()))
			{
				mng->BackToOrign();
				(*iter)->GetItem()->Nomalstate(mng->GetPlayer());
				(*iter)->GetItem()->ItemCall();
				(*iter)->Release();
				delete (*iter);
				iter = mng->GetItemBlock()->erase(iter);
				//itemstate = false; 처음 깨끗한 상태를 얻어온 뒤 아이템을 먹을때마다 다시 되돌릴 방법 생각하기
			}
			else if ((*iter)->Getpos().y > 780)
			{
				(*iter)->Release();
				delete (*iter);
				iter = mng->GetItemBlock()->erase(iter);
			}
			else
			{
				(*iter)->MovebyY(move_y);
				iter++;
			}
		}
	}
}

float OutPut::GetSpeed()
{
	return ballSpeed;
}

void OutPut::SetSpeed(float speed)
{
	ballSpeed = speed;
}

LineBoolList OutPut::myIntersectRect(Block * rect, Vector2 line1, Vector2 line2)
{
	LineBoolList intersectLineList = { FALSE };

	Vector2 rectTopLeft = { (float)rect->GetRect().left, (float)rect->GetRect().top };
	Vector2 rectTopRight = { (float)rect->GetRect().right, (float)rect->GetRect().top };
	Vector2 rectBottomLeft = { (float)rect->GetRect().left, (float)rect->GetRect().bottom };
	Vector2 rectBottomRight = { (float)rect->GetRect().right, (float)rect->GetRect().bottom };

	intersectLineList.bLeft = IntersectLine(rectTopLeft, rectBottomLeft, line1, line2);
	intersectLineList.bRight = IntersectLine(rectTopRight, rectBottomRight, line1, line2);
	intersectLineList.bTop = IntersectLine(rectTopLeft, rectTopRight, line1, line2);
	intersectLineList.bBottom = IntersectLine(rectBottomLeft, rectBottomRight, line1, line2);

	return intersectLineList;
}

bool OutPut::IntersectLine(Vector2 line1, Vector2 line2, Vector2 line3, Vector2 line4)
{
	float den = ((line4.y - line3.y) * (line2.x - line1.x)) - ((line4.x - line3.x) * (line2.y - line1.y));

	if (den == 0) {
		return FALSE;
	}
	else {
		float ua = ((line4.x - line3.x) * (line1.y - line3.y) - (line4.y - line3.y) * (line1.x - line3.x)) / den;
		float ub = ((line2.x - line1.x) * (line1.y - line3.y) - (line2.y - line1.y) * (line1.x - line3.x)) / den;

		if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}


