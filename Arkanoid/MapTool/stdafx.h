// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment (lib, "msimg32.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <CommCtrl.h>
#include <tchar.h>


#include <vector>

#include "TSingle.h"

#include "define.h"
#include "Struct.h"
#include "Resource.h"

#include "global.h"

#include "cBlock.h"
#include "cMap.h"

#include "Image.h"
#include "DlgBlock.h"
#include "DlgControl.h"


#include "MapTool.h"


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
