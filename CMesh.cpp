#include "CMesh.h"
#include "CUtility.h"

CMesh::CMesh()
{
	m_pMesh=NULL;
	m_numMaterials=NULL;
	m_pMeshMaterials=NULL;
	m_ppMeshTextures=NULL;
}

BOOL CMesh::Load(LPDIRECT3DDEVICE9 d3ddev, char* file,HWND hWnd1 )
{
	hWnd=hWnd1;
	LPD3DXBUFFER materialBuffer;
	char path[MAX_PATH];
	if(CUtility::GetMediaFile(file,path))
	{
		
		HRESULT hr=D3DXLoadMeshFromX(file,D3DXMESH_MANAGED,d3ddev,NULL,&materialBuffer,NULL,&m_numMaterials,&m_pMesh);
		if(FAILED(hr))
		{
			MessageBox(hWnd1,"Mesh loading failed","CMesh",MB_OK);
			return FALSE;
		}
		else
		{
			//Show Material and texture information

			

			D3DXMATERIAL* pMaterials=(D3DXMATERIAL*)materialBuffer->GetBufferPointer(); 

			m_pMeshMaterials=new D3DMATERIAL9[m_numMaterials];

			m_ppMeshTextures = new LPDIRECT3DTEXTURE9[m_numMaterials];

			//Copy the material and exture to the member arrays

			for(DWORD  i=0;i<m_numMaterials;i++)
			{
				

				m_pMeshMaterials[i]=pMaterials[i].MatD3D;
				m_pMeshMaterials[i].Ambient=m_pMeshMaterials[i].Diffuse;

				//Create Texture if it exists

				m_ppMeshTextures[i]=NULL;

				if(pMaterials[i].pTextureFilename)
				{
					
					CUtility::GetMediaFile(pMaterials[i].pTextureFilename,path);
					if(FAILED(D3DXCreateTextureFromFile(d3ddev,path,&m_ppMeshTextures[i])))
					{
						MessageBox(hWnd1,"Texture loading failed","CMesh",MB_OK);
						//return FALSE;
					}
				}

			}

			materialBuffer->Release();
			return TRUE;

		}
	}
	else
	{
		return FALSE;
	}
}

void CMesh::Release()
{
	if(m_ppMeshTextures)
	{
		for(DWORD i=0;i<m_numMaterials;i++)
		{
			if(m_ppMeshTextures[i])
			m_ppMeshTextures[i]->Release();
		}
	}

	if(m_pMesh)
	{
		MessageBox(hWnd,"  value in mesh ","CMesh",MB_OK);
	m_pMesh->Release();
	}
	else
		MessageBox(hWnd," no value in mesh ","CMesh",MB_OK);

}
