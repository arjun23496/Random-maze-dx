#ifndef CCUBE_H
#define CCUBE_H

#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include<d3dx9.h>

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#define CUSTOMFVF (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

class CCube
{

private:
	struct CUSTOMVERTEX{FLOAT X,Y,Z;D3DVECTOR NORMAL;FLOAT u,v;};	//The vetex structure containing the vertices
	int vno;														//The no of vertices
	int primno;														//the no of primitives
	LPDIRECT3DINDEXBUFFER9 i_buffer;								//the index buffer
	LPDIRECT3DVERTEXBUFFER9 v_buffer;								//The vertex buffer
public:
	CCube();
	void init_cube(LPDIRECT3DDEVICE9 d3ddev);
	int no_vertices();
	int no_prim();
	int size_vertexdata();
	DWORD getFVF();
	LPDIRECT3DINDEXBUFFER9 get_ibuffer();
	LPDIRECT3DVERTEXBUFFER9 get_vbuffer();
};



#endif