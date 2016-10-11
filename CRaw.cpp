#include "CRaw.h"

CRaw::CRaw()
{
	f=0;
	tv_buffer=NULL;
	ti_buffer=NULL;
	
}

BOOL CRaw::init_terrain(LPDIRECT3DDEVICE9 d3ddev1,char file[],HWND hWnd)
{
	d3ddev=d3ddev1;
	char path[MAX_PATH];
	CUtility::GetMediaFile(file,path);
	terrfile.open(path,ios::binary);

	if(CUtility::GetMediaFile("terraingrass.png",path))
	{
		HRESULT hr;
		hr=D3DXCreateTextureFromFile(d3ddev,"terraingrass.png",&t_texture);
		if(FAILED(hr))
		{
			MessageBox(hWnd,"texture loading failed","init_terrain",MB_OK);
			f=1;
		}
	}


	if(f==0)
	{
		float h=0.0;
		float prevh=0.0;
		

	
    if (terrfile.is_open())
     {

        for (int x=0;x< WIDTH;x++)        {

            for (int y=0; y< HEIGHT;y++)            {
                vertices[y*WIDTH + x].X = -x;
                vertices[y*WIDTH + x].Y = y;
				prevh=terrfile.get()/100;
				h=terrfile.get()/100;
                vertices[y*WIDTH + x].Z = 0;
				//vertices[y*WIDTH + x].color = 0xffffffff;
				vertices[y*WIDTH+x].NORMAL=D3DXVECTOR3(x,y,1);
				if(prevh<h)
				{
				vertices[y*WIDTH + x].NORMAL=D3DXVECTOR3(0,1,0);
				}
				else
					vertices[y*WIDTH+x].NORMAL=D3DXVECTOR3(0,1,0);
				if(x%2==0)
			{
				if(y%2==0)
				{
					vertices[y*WIDTH+x].u=0;
					vertices[y*WIDTH+x].v=1;
				}
				else
				{
					vertices[y*WIDTH+x].u=0;
					vertices[y*WIDTH+x].v=0;
				}
			}
			else
			{
				if(y%2==0)
				{
					vertices[y*WIDTH+x].u=1;
					vertices[y*WIDTH+x].v=1;
				}
				else
				{
					vertices[y*WIDTH+x].u=1;
					vertices[y*WIDTH+x].v=0;
				}
			}
            }
        }
    }else{
        MessageBox(hWnd,"HeighData file not found!","FillVertices()",MB_OK);
    }

    
	terrfile.close();

	d3ddev->CreateVertexBuffer(sizeof(vertices),0,CUSTOMFVF,D3DPOOL_MANAGED,&tv_buffer,NULL);


	VOID* p_Vertices;
     if (FAILED(tv_buffer->Lock(0, sizeof(vertices), (void**)&p_Vertices, 0)))
     {
         MessageBox(hWnd,"Error trying to lock","FillVertices()",MB_OK);
     }else{
         memcpy(p_Vertices, vertices, WIDTH*HEIGHT*sizeof(CUSTOMVERTEX));
         tv_buffer->Unlock();
     }
 

	
 

    for (int x=0;x< WIDTH-1;x++)    {

        for (int y=0; y< HEIGHT-1;y++)        {
            indices[(x+y*(WIDTH-1))*6+2] = x+y*WIDTH;
            indices[(x+y*(WIDTH-1))*6+1] = (x+1)+y*WIDTH;
            indices[(x+y*(WIDTH-1))*6] = (x+1)+(y+1)*WIDTH;

            indices[(x+y*(WIDTH-1))*6+3] = (x+1)+(y+1)*WIDTH;
            indices[(x+y*(WIDTH-1))*6+4] = x+y*WIDTH;
            indices[(x+y*(WIDTH-1))*6+5] = x+(y+1)*WIDTH;

        }
    }

    
    // create an index buffer interface called i_buffer
    d3ddev->CreateIndexBuffer(sizeof(indices),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &ti_buffer,
                              NULL);

	VOID* p_Indices;
    if (FAILED(ti_buffer->Lock(0, sizeof(indices), (void**)&p_Indices, 0)))
    {
        MessageBox(hWnd,"Error trying to lock","FillIndices()",MB_OK);
    }else{
        memcpy(p_Indices, indices, (WIDTH-1)*(HEIGHT-1)*6*sizeof(short));
        ti_buffer->Unlock();
    }

	}
	else
		return FALSE;
}

void CRaw::render_terrain()
{
	d3ddev->SetFVF(CUSTOMFVF);
	d3ddev->SetTexture(0,t_texture);
	d3ddev->SetStreamSource(0,tv_buffer,0,sizeof(CUSTOMVERTEX));
	d3ddev->SetIndices(ti_buffer);
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,WIDTH*HEIGHT,0,(WIDTH-1)*(HEIGHT-1));
}

CRaw::~CRaw()
{
	if(t_texture)
	t_texture->Release();

	if(tv_buffer)
		tv_buffer->Release();

	if(ti_buffer)
		ti_buffer->Release();
}
