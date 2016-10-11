#include "CLightMat.h"
#include "PxPhysicsAPI.h"

CLightMat::CLightMat()
{
	ZeroMemory(&light,sizeof(D3DLIGHT9));
	ZeroMemory(&material,sizeof(D3DMATERIAL9));
}

void CLightMat::init_light()
{
			
			light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
			light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
			light.Direction = D3DXVECTOR3(0.0f, -1.0f, 1.0f);	
}

void CLightMat::init_material()
{
	material.Diffuse = D3DXCOLOR(1.0,1.0,1.0,1.0);    // set diffuse color to white
	material.Ambient = D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f);    // set ambient color to white
	material.Power=100;
}

D3DLIGHT9 CLightMat::get_light(void)
{
	return light;
}

D3DMATERIAL9 CLightMat::get_material(void)
{
	return material;
}
