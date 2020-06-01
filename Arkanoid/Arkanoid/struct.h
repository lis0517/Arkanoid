#pragma once

#include "Block.h"

struct DataInfo
{
	Vector2		_pos;
	Vector2		_size;
	eItem_List  _itemList;
	BlockType	_type;
	eBlock_List _blockList;
	DWORD		_brush;
	DWORD		_pen;
};