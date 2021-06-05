#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class ScreenCapturer {
private:
	int windowWidth;
	int windowHeight;
	int cx; //center-x
	int cy; // center-y
	int x1, x2, y1, y2; // left-top, right-top, left-down, right-down
	HWND hWnd;
	HDC hWindowDC;
	HDC hCaptureDC;

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