#ifndef CFIRE_H
#define CFIRE_H

#include<time.h>
#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<stdlib.h>
#include<time.h>
// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#define CUSTOMFVF (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
#define LENGTH 10
#define HEIGHT 50

class CFire
{
public:
	CFire();
	~CFire(){Release();};
	void render_fire(int strno);
	void init_device(LPDIRECT3DDEVICE9 d3dtemp,HWND hWnd1);
private:
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DVERTEXBUFFER9 fv_buffer;
	struct CUSTOMVERTEX { FLOAT x,y,z,rhw;D3DXCOLOR color;};
	CUSTOMVERTEX vertices[1000];
	void Release();
	HWND hWnd;
	char primno[10];
	
};

#endif