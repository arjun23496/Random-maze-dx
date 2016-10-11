#ifndef CGRAPHICS_H
#define CGRAPHICS_H 


#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include<d3dx9.h>
 

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class CGraphics
{
public:
    CGraphics();
    ~CGraphics() { Release(); }
   BOOL Initialize( HWND hWnd, BOOL bWindowed, int width, int height);
    void Release();
	BOOL Reset();
	LPDIRECT3D9       GetD3D()    { return d3d; }
	LPDIRECT3DDEVICE9 GetDevice() { return d3ddev; } 

    BOOL Windowed;

	LPDIRECT3D9             d3d;
	LPDIRECT3DINDEXBUFFER9 i_buffer;
	LPDIRECT3DVERTEXBUFFER9 v_buffer;
    DWORD FVF;

private:
    
    
    LPDIRECT3DDEVICE9       d3ddev;
    D3DPRESENT_PARAMETERS   d3dpp;
	
    
}; 

#endif