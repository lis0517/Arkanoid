#include "stdafx.h"
#include "MapTool.h"

int g_BlockCellSize = 0;

MapTool::MapTool()
{
	m_Cellsize = 32;
	g_BlockCellSize = m_Cellsize;
}


MapTool::~MapTool()
{
}

void MapTool::SetControlBlock()
{
	//m_DlgControl.SelectBlock()
}

int MapTool::GetBlockWidth()
{
	return 0;
}

int MapTool::GetBlockHeigth()
{
	return 0;
}

int MapTool::GetSize()
{
	return 0;
}

void MapTool::Init()
{
	_DlgControl.Init();
	_DlgBlock.Init();
	//_ImageMng.Init();
	SetForegroundWindow(g_hWnd);


}

void MapTool::Update()
{
	
}

void MapTool::Render()
{
}
