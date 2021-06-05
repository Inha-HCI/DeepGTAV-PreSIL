#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <afxwin.h>
class ScreenCapturer {
private:
	int windowWidth;
	int windowHeight;

	HWND hWnd;
	HDC hWindowDC;
	HDC hCaptureDC;
	CWnd hCaptureWnd;
	HBITMAP hCaptureBitmap;
	BITMAPINFOHEADER info;
public:
	int imageWidth;
	int imageHeight;
	int length;

	UINT8* pixels;


	ScreenCapturer(int frameWidth, int frameHeight);
	~ScreenCapturer();
	void capture();
	
};