#ifndef CFRAME_H
#define CFRAME_H

#include<time.h>
#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<stdlib.h>
#include "CGraphics.h"
#include "CMesh.h"
#include "CRaw.h"
#include "CFire.h"

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")


class CFrame
{

public:
	CFrame();
	~CFrame();
	void renderframe();
	void initgraphics(HWND hWnd);
	void modtarget(int x,int y);
	void KeyHandle(int mcode);
private:

	void SetMesh(CMesh* pMesh);
	void RenderMesh();
	

	LPDIRECT3DDEVICE9 d3ddev;
	CGraphics obj;
	struct CUSTOMVERTEX{FLOAT X,Y,Z;D3DVECTOR NORMAL;FLOAT u,v;};
	D3DXMATRIX matView;
	D3DXMATRIX matProjection;
	D3DXMATRIX matRotateY;
	LPD3DXFONT fpsfont;
	time_t ti;
	time_t tf;
	RECT rect;
	int noframes;
	int td;
	int fps;
	char fpsstring[10];
	D3DXVECTOR3 m_lookat;
	POINT finalpos;
	D3DXVECTOR3 m_eyePos;

	//The circle definition

	double xcocir,zcocir,angle;

	CMesh* fm_pMesh;

	HWND hWnd;

	D3DXMATRIX matScale;
	D3DXMATRIX matTranslate;
	HWND hWnd1;

	CMesh m; //The mesh instance object 

	CRaw terr;	//The terrrain class object
	int fterr;
	char eyex[10],eyey[10],eyez[10];
	int posx[21],posz[21];
	CFire fire;
};

#endif