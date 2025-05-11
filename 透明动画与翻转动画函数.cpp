#include<iostream>
#include<easyx.h>
#include<Windows.h>
using namespace std;


#pragma comment(lib,"MSIMG32.LIB")

void putimagealpha(int x, int y, IMAGE* img)//ÊµÏÖÍ¸Ã÷Í¼Æ¬
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void flipAmination(IMAGE* img1, IMAGE* img2, int length)//Í¼Æ¬·­×ª
{
	for (int i = 0; i < length; i++)
	{
		int width = img1[i].getwidth(), height = img1[i].getheight();
		Resize(&img2[i], width, height);
		DWORD* color_buffer_left_img = GetImageBuffer(&img1[i]);
		DWORD* color_buffer_right_img = GetImageBuffer(&img2[i]);
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int idx_left_img = width * y + x;
				int idx_right_img = width * y + (width - x - 1);
				color_buffer_right_img[idx_right_img] = color_buffer_left_img[idx_left_img];
			}
		}
	}
}

void sketch_image(IMAGE* img1, IMAGE* img2)  //ÉÁ°×Í¼Æ¬
{
	int w = img1->getwidth();
	int h = img1->getheight();
	Resize(img2, w, h);
	DWORD* src_buffer = GetImageBuffer(img1);
	DWORD* dst_buffer = GetImageBuffer(img2);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx = y * w + x;
			dst_buffer[idx] = BGR(RGB(255, 255, 255)) | (src_buffer[idx] & 0xFF000000);
		}
	}
}
