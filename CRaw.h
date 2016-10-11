#ifndef CRAW_H
#define CRAW_H


#include<time.h>
#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include<d3dx9.h>
#include "CUtility.h"
#include <fstream>

using namespace std;

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#define WIDTH 100
#define HEIGHT 100

#define CUSTOMFVF (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_TEX1)
struct CUSTOMVERTEX {FLOAT X,Y,Z;FLOAT u,v;D3DXVECTOR3 NORMAL; };

class CRaw
{
	public:
		CRaw();
		~CRaw();
		BOOL init_terrain(LPDIRECT3DDEVICE9 d3ddev1,char file[],HWND hWnd);
		void render_terrain(void);
	private:
		std::ifstream terrfile;
		int f;	//flag containing the error information
		LPDIRECT3DVERTEXBUFFER9 tv_buffer;
		LPDIRECT3DINDEXBUFFER9 ti_buffer;
		LPDIRECT3DDEVICE9 d3ddev;
		IDirect3DTexture9 *t_texture;
		CUSTOMVERTEX vertices[WIDTH*HEIGHT];
		short indices[(WIDTH)*(HEIGHT)*6];
};


#endif