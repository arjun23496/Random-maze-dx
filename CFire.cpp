#include "CFire.h"

CFire::CFire()
{
	d3ddev=NULL;
	fv_buffer=NULL;
	srand(time(NULL));
	

}

void CFire::render_fire(int strno)
{
	
	static int no_vert=0;
	for(int i=0;i<HEIGHT&&no_vert<2000;i++)
	{
		for(int j=HEIGHT;j>i&&no_vert<2000;j--)
		{
			vertices[no_vert].x=rand()%(LENGTH);
			vertices[no_vert].z=rand()%(LENGTH);
			vertices[no_vert].y=10+i;
			vertices[no_vert].rhw=1.0f;
			vertices[no_vert].color=D3DXCOLOR(255.0f,102.0f,0.0f,1.0f);
			no_vert++;
		}
	}

	
	//itoa(no_vert,primno,10);
	//MessageBox(hWnd,primno,"render_fire()",MB_OK);

	VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    if(FAILED(fv_buffer->Lock(0, 0, (void**)&pVoid, 0)))
		MessageBox(hWnd,"vertexlocking failed","render_fire()",MB_OK);
	else
	{
	 memcpy(pVoid, vertices, sizeof(vertices));
    fv_buffer->Unlock();
	}

	d3ddev->SetFVF(CUSTOMFVF);
	d3ddev->SetStreamSource(1,fv_buffer,0,sizeof(CUSTOMVERTEX));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST,0,no_vert);

	//fv_buffer->Release();

	

}

void CFire::Release()
{
	fv_buffer->Release();
}

void CFire::init_device(LPDIRECT3DDEVICE9 d3dtemp,HWND hWnd1)
{
	d3ddev=d3dtemp;
	hWnd=hWnd1;
	d3ddev->CreateVertexBuffer(2000*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &fv_buffer,
                               NULL);
}