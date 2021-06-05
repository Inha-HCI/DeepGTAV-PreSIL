#include "ScreenCapturer.h"
#include "lib/natives.h"
#include <stdlib.h>

ScreenCapturer::ScreenCapturer(int frameWidth, int frameHeight){
	imageWidth = frameWidth;
	imageHeight = frameHeight;

	// Round up the scan line size to a multiple of 4
	length = ((imageWidth * 3 + 3) / 4 * 4) * imageHeight;

	//Screen capture buffer
	GRAPHICS::_GET_SCREEN_ACTIVE_RESOLUTION(&windowWidth, &windowHeight);
	hWnd = ::FindWindow(NULL, "Grand Theft Auto V");
	
	hWindowDC = GetDC(NULL); //get window DC
	cx = int(GetSystemMetrics(SM_CXSCREEN)/2);
	cy = int(GetSystemMetrics(SM_CYSCREEN)/2);
	
	x1 = cx - int(imageWidth/2);
	y1 = cy - int(imageHeight/2);
	x2 = cx + int(imageWidth / 2);
	y2 = cy + int(imageHeight / 2);

	hCaptureDC = CreateCompatibleDC(hWindowDC);
	hCaptureBitmap = CreateCompatibleBitmap(hWindowDC, imageWidth, imageHeight);
	SelectObject(hCaptureDC, hCaptureBitmap);
	SetStretchBltMode(hCaptureDC, COLORONCOLOR);

	pixels = (UINT8*)malloc(length);
	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biPlanes = 1;
	info.biBitCount = 24;
	info.biWidth = imageWidth;
	info.biHeight = -imageHeight;
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;
}

ScreenCapturer::~ScreenCapturer(){
	free(pixels);
	ReleaseDC(hWnd, hWindowDC);
	DeleteDC(hCaptureDC);
	DeleteObject(hCaptureBitmap);
}

void ScreenCapturer::capture() {
	StretchBlt(hCaptureDC, 0, 0, imageWidth, imageHeight, hWindowDC, x1, y1, windowWidth, windowHeight, SRCCOPY);
	GetDIBits(hCaptureDC, hCaptureBitmap, 0, imageHeight, pixels, (BITMAPINFO*)&info, DIB_RGB_COLORS);
}