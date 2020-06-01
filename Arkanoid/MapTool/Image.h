#pragma once
class Image
{
private:
	HDC			_MemDC;
	HBITMAP		_Bit, _oldBit;
	BYTE *		_Data;
	DWORD		_Pitch;
	ImageInfo	_Info;
private:
	HBITMAP GetBit(TCHAR * Name);
	void Flip();
public:
	Image(TCHAR * Name, ImageInfo info);
	~Image();

	void Render(HDC hdc, int x, int y, bool key, int frameX, int frameY);
	void Render(HDC hdc, int fLeft, int fTop, int fRight, int fBottom, int sLeft, int sTop, int sRight, int sBottom);

	HDC GetMemDC(){ return _MemDC; }
	int GetImageWidth() const { return _Info._FWidth; }
	int GetImageHeight() const { return _Info._FHeight; }
};


class ImageMng : public Singleton<ImageMng>
{
private:
	std::vector<Image*>		_Image;
	HDC						_hdc;
	HDC						_mDlghdc;
	HDC						_Back;
	HDC						_DlgBack;
public:
	ImageMng();
	~ImageMng();
	void Init();
	void Release();
	void CreateImage(TCHAR * fileName, int framex, int framey);

	Image* GetImage(int num) { return _Image[num]; }
	HDC GetHDC() { return _hdc; }
	HDC GetBack() { return _Back; }
	HDC GetDlgBack() { return _DlgBack; }

	Image* operator[](int index) { return _Image[index]; }

};

#define SIMG ImageMng::GetInstance()
#define RGB_A RGB(0,0,0)
