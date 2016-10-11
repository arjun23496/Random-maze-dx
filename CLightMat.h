#ifndef CLIGHTMAT_H
#define CLIGHTMAT_H

#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include<d3dx9.h>
 

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class CLightMat
{
	public:
		
		CLightMat();
		
		void init_light();
		
		void init_material();
		
		D3DLIGHT9 get_light(void);
		
		D3DMATERIAL9 get_material(void);
		

private:
	D3DLIGHT9 light;
	D3DMATERIAL9 material;

};


#endif