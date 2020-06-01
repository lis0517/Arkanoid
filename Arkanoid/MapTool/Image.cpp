#include "stdafx.h"
#include "Image.h"


Image::Image(TCHAR * Name, ImageInfo info)
{
	_Info = info;
	HDC hdc = GetDC(g_hWnd);
	_MemDC = CreateCompatibleDC(hdc);
	_Bit = GetBit(Name);
	_oldBit = (HBITMAP)SelectObject(_MemDC, _Bit);

	ReleaseDC(g_hWnd, hdc);
}

Image::~Image()
{
	SelectObject(_MemDC, _oldBit);
	DeleteObject(_Bit);
	DeleteDC(_MemDC);
}

HBITMAP Image::GetBit(TCHAR * Name)
{
	HANDLE hFile;
	BITMAPFILEHEADER bHeader;//비트맵 파일 자체 정보
	BITMAPINFO *	 bInfo;
	DWORD			 Read;
	DWORD			 InfoSize;
	HBITMAP			 bit;

	hFile = CreateFile(Name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hFile, &bHeader, sizeof(bHeader), &Read, NULL);
	InfoSize = bHeader.bfOffBits - sizeof(bHeader);
	bInfo = (BITMAPINFO*) new BYTE[InfoSize];
	ReadFile(hFile, bInfo, InfoSize, &Read, NULL);

	bInfo->bmiHeader.biHeight *= -1;
	bit = CreateDIBSection(NULL, bInfo, DIB_RGB_COLORS, (void**)&_Data, NULL, 0);
	bInfo->bmiHeader.biHeight *= -1;

	_Info._Width = bInfo->bmiHeader.biWidth;
	_Info._Height = bInfo->bmiHeader.biHeight;
	_Info._FWidth = _Info._Width / _Info._FrameXmax;
	_Info._FHeight = _Info._Height / _Info._FrameYmax;
	

	ReadFile(hFile, _Data, bHeader.bfSize - bHeader.bfOffBits, &Read, NULL);
	Flip();

	CloseHandle(hFile);
	delete[] bInfo;

	HBITMAP bit;

	return bit;
}

void Image::Flip()
{
	int			i;

	BYTE*	pTemp;

	pTemp = new BYTE[_Pitch];

	for (i = 0; i < _Info._Height / 2; i++)
	{
		memcpy(pTemp, &_Data[i * _Pitch], _Pitch);
		memcpy(&_Data[i * _Pitch], &_Data[(_Info._Height - 1 - i)  * _Pitch], _Pitch);
		memcpy(&_Data[(_Info._Height - 1 - i)  * _Pitch], pTemp, _Pitch);
	}
	delete[] pTemp;
}


void Image::Render(HDC hdc, int x, int y, bool key, int frameX, int frameY)
{
	if(key)
	{
		TransparentBlt(hdc, x, y, _Info._FWidth, _Info._FHeight,
			_MemDC, frameX * _Info._Width, frameY * _Info._Height, _Info._Width, _Info._Height,RGB_A);
	}
	else
	{
		BitBlt(hdc, x, y, _Info._FWidth, _Info._FHeight,
			_MemDC, frameX * _Info._Width, frameY * _Info._Height, SRCCOPY);
	}
}

void Image::Render(HDC hdc, int fLeft, int fTop, int fRight, int fBottom, int sLeft, int sTop, int sRight, int sBottom)
{
	TransparentBlt(hdc, fLeft, fTop, fRight, fBottom, _MemDC, sLeft, sTop, sRight, sBottom, RGB_A);
}



ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
	Release();
}

void ImageMng::Init()
{
	_hdc = GetDC(g_hWnd);

	CreateImage(TEXT("Image/Map.bmp"), 1, 1);
	CreateImage(TEXT("Image/Nomal.bmp"), 1, 1);
	CreateImage(TEXT("Image/Unique.bmp"), 1, 1);

	_Back = _Image[IMG_BACK]->GetMemDC();
	_DlgBack = _Image[IMG_DLGBACK]->GetMemDC();
}

void ImageMng::Release()
{
	for (int i = 0; i < _Image.size(); ++i)
	{
		delete _Image[i];
	}
	_Image.clear();
}

void ImageMng::CreateImage(TCHAR * fileName, int framex, int framey)
{
	ImageInfo info;
	memset(&info, 0x0000, sizeof(info));
	info._FrameXmax = framex;
	info._FrameYmax = framey;

	Image * temp = new Image(fileName, info);

	_Image.push_back(temp);
}
