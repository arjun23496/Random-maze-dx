#include "CGraphics.h"
#include "CLightMat.h"
#include "CCube.h"
#include "CMesh.h"

//Default Constructor


CGraphics::CGraphics() 
{
	d3ddev=NULL;
	d3d=NULL;
}

void CGraphics::Release()
{
}

BOOL CGraphics::Initialize(HWND hWnd, BOOL bWindowed, int width,int height)
{
	

	//Creating and initializing the direct 3d device
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	
    

	 ZeroMemory(&d3dpp, sizeof(d3dpp));

	 //Initialise the window making parameters using the d3dpp struct

	 d3dpp.Windowed=TRUE;					//The showing mode
	 d3dpp.SwapEffect= D3DSWAPEFFECT_DISCARD;	//The effect used for displaying
	 d3dpp.hDeviceWindow=hWnd;					//Handle to the window making the direct 3d device
	 d3dpp.BackBufferFormat=D3DFMT_X8R8G8B8;	//The buffer definition format
	 d3dpp.BackBufferWidth=width;				//The back buffer width
	 d3dpp.BackBufferHeight=height;				//The back buffer height
	 d3dpp.EnableAutoDepthStencil=TRUE;			//This is to enable autostencil for 3d effects
	 d3dpp.AutoDepthStencilFormat=D3DFMT_D16;	//The autostencil format setting to 16 bit format

	 //Create a direct 3d device using the information given in the d3dpp struct

	HRESULT hr;
	 
	hr= d3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&d3ddev);

	if(FAILED(hr))
	{
		MessageBox(hWnd,"Device Initialisation Failed","Device Initialisation",MB_OK);
		return FALSE;
	}
	else
	{
		CCube cube;
		cube.init_cube(d3ddev);

		CMesh obj;
		obj.Load(d3ddev,"temple.x",hWnd);

		v_buffer=cube.get_vbuffer();
		i_buffer=cube.get_ibuffer();
		FVF=cube.getFVF();
		CLightMat lmobj;
		lmobj.init_light();
		lmobj.init_material();
		

		 d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);    // turn on the 3D lighting
		 d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
		 d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));    // ambient light
		 d3ddev->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);	//Rectifies scaling problem
		 d3ddev->SetLight(0,&(lmobj.get_light()));//Set the lighting
		 d3ddev->LightEnable(0,TRUE);
		 d3ddev->SetMaterial(&lmobj.get_material());//Set the material
		 d3ddev->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

		return TRUE;
	}
}

BOOL CGraphics::Reset()
{
	HRESULT hr;

	hr=d3ddev->Reset(&d3dpp);
	if(FAILED(hr))
		return FALSE;
	else
		return TRUE;

}

