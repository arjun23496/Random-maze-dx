#include "CFrame.h"
#include "CMesh.h"
#include "CFire.h"


	CFrame::~CFrame()
{
	fpsfont->Release();

}

	CFrame::CFrame()
	{

		srand(time(NULL));
		for(int i=0;i<=20;i++)
		{
			posx[i]=1*rand()%500;
			posz[i]=-1*rand()%500;
		}

		fterr=0;
		td=0;
		noframes=0;
		ti=time(NULL);
		tf=time(NULL);
		

		finalpos.x=384;
		angle=0;
		xcocir=10*cos(angle);
		zcocir=10*sin(angle);
		m_lookat.x=0.0f;
		m_lookat.y=10.0f;
		m_lookat.z=0.0f;
		m_eyePos.x=-33.0f;
		m_eyePos.y=10.0f;
		m_eyePos.z=43.0f;
		
	}

	void CFrame::initgraphics(HWND hWnd)
	{
		hWnd1=hWnd;
		if(obj.Initialize(hWnd,TRUE,1366,768))
		{
			d3ddev=obj.GetDevice();
		}

		HRESULT hr;
		hr=D3DXCreateFont(d3ddev,     //D3D Device

                     22,               //Font height

                     0,                //Font width

                     FW_NORMAL,        //Font Weight

                     1,                //MipLevels

                     false,            //Italic

                     DEFAULT_CHARSET,  //CharSet

                     OUT_DEFAULT_PRECIS, //OutputPrecision

                     ANTIALIASED_QUALITY, //Quality

                     DEFAULT_PITCH|FF_DONTCARE,//PitchAndFamily

                     "Arial",          //pFacename,

                     &fpsfont);         //ppFont

		

		if(!m.Load(d3ddev,"scene.x",hWnd))
			MessageBox(hWnd,"Mesh Loaading failed","frame.cpp",MB_OK);
			

		SetMesh(&m);
		
		if(!terr.init_terrain(d3ddev,"terrain.raw",hWnd))
			fterr=1;
		
		fire.init_device(d3ddev,hWnd);

	}

	void CFrame::renderframe()
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
        d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

		d3ddev->BeginScene();

		// Here is the code to draw the cube................................................................

		d3ddev->SetFVF(obj.FVF);
	

    // set the view transform
    
    D3DXMatrixLookAtLH(&matView,
    &m_eyePos,    // the camera position
    &m_lookat,      // the look-at position
    &D3DXVECTOR3 (0.0f, 1.0f, 0.0f));    // the up direction
    d3ddev->SetTransform(D3DTS_VIEW, &matView);

    // set the projection transform
    
    D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45),
                               1/1,
                               1.0f,    // the near view-plane
                               10000.0f);    // the far view-plane
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);

    // set the world transform
    static float index = 0.0f; index+=0.03f;
    static float index1=0.0f;index1+=0.03f;
   
    

    // select the vertex and index buffers to use
	d3ddev->SetStreamSource(0, obj.v_buffer, 0, sizeof(CUSTOMVERTEX));
    d3ddev->SetIndices(obj.i_buffer);

	//The terrain rendering code///////////////////////////////////////////////////////////////////////////////////////////////////
	for(index1=0;index1<=500;index1+=70)
	{

	for(index=0;index<=1000;index+=120)
	{

	D3DXMatrixScaling(&matScale,10,10,10);
	D3DXMatrixTranslation(&matTranslate,index,index1,0);
	D3DXMatrixRotationX(&matRotateY,3*D3DX_PI/2);
	d3ddev->SetTransform(D3DTS_WORLD,&(matScale*matTranslate*matRotateY));
	if(fterr==0);
	terr.render_terrain();
	}
	
	}
	//Display the frames per second//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	td=difftime(tf,ti);
	if(td!=0)
	{
		fps=noframes/td;
		tf=time(NULL);
		ti=time(NULL);
		noframes=0;

		

		itoa(fps,fpsstring,10);

	}
	tf=time(NULL);

	rect.top=50;
	rect.left=0;
	rect.bottom=200;
	rect.right=200;
		
	fpsfont->DrawText(NULL,        //pSprite

                               fpsstring,      //pString

                               -1,          //Count

                                &rect,  //pRect

                                DT_LEFT|DT_WORDBREAK, //Format,

                                0xFFFFFFFF); //Color


	//end of diaplay of frames per second////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // draw the cube
   // d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12); 




	//To  display the position of eye

	rect.top=0;
	rect.left=0;
	rect.bottom=50;
	rect.right=50;

	itoa(m_eyePos.x,eyex,10);

	fpsfont->DrawText(NULL,        //pSprite

                                eyex,      //pString

                                -1,          //Count

                                &rect,  //pRect

                                DT_LEFT|DT_WORDBREAK, //Format,

                                0xFFFFFFFF); //Color

	rect.top=0;
	rect.left=50;
	rect.bottom=50;
	rect.right=100;

	itoa(m_eyePos.y,eyey,10);

	fpsfont->DrawText(NULL,        //pSprite

                               eyey,      //pString

                                -1,          //Count

                                &rect,  //pRect

                                DT_LEFT|DT_WORDBREAK, //Format,

                                0xFFFFFFFF); //Color

	rect.top=0;
	rect.left=100;
	rect.bottom=50;
	rect.right=150;

	itoa(m_eyePos.z,eyez,10);

	fpsfont->DrawText(NULL,        //pSprite

                                eyez,      //pString

                                -1,          //Count

                                &rect,  //pRect

                                DT_LEFT|DT_WORDBREAK, //Format,

                                0xFFFFFFFF); //Color




	static int mult=0;
	//mult=0;
	for(mult=0;mult<=20;mult++)
	{
	D3DXMatrixScaling(&matScale,5,5,5);
	D3DXMatrixTranslation(&matTranslate,posx[mult],25,posz[mult]);
	d3ddev->SetTransform(D3DTS_WORLD,&(matScale*matTranslate));

	RenderMesh();
	}
	
		//End of mesh drawing code...........................................................................
	/*D3DXMatrixTranslation(&matTranslate,8,10,-3);
	d3ddev->SetTransform(D3DTS_WORLD,&(matTranslate*matScale));
	fire.render_fire(1);*/
		

		d3ddev->EndScene();

		d3ddev->Present(NULL,NULL,NULL,NULL);
		noframes++;
		
		
	}

	void CFrame::modtarget(int x,int y)
	{
		if(finalpos.x-x<0)
			angle-=0.030;
		else if(finalpos.x-x>0)
			angle+=0.030;
		if(finalpos.y-y>0&&m_lookat.y<1000&&m_lookat.y>-1000)
			m_lookat.y+=0.35;
		if(finalpos.y-y<0&&m_lookat.y<1000&&m_lookat.y>-1000)
			m_lookat.y-=0.35;

		finalpos.x=x;
		finalpos.y=y;
		xcocir=10*cos(angle);
		zcocir=10*sin(angle);
		m_lookat.x=xcocir+m_eyePos.x;
		m_lookat.z=zcocir+m_eyePos.z;
	}

	void CFrame::RenderMesh()
	{
		if(d3ddev&&fm_pMesh)
		{
			
			DWORD numMaterials=fm_pMesh->GetNumMaterials();
			
			for(DWORD i=0;i<numMaterials;i++)
			{
				
				
				
				d3ddev->SetMaterial(fm_pMesh->GetMeshMaterial(i));
				
				
				d3ddev->SetTexture(0,fm_pMesh->GetMeshTexture(i));
				
				fm_pMesh->GetMesh()->DrawSubset(i);
				
			}
		}
	}

	void CFrame::SetMesh(CMesh* pMesh)
	{
		fm_pMesh=pMesh;
	}

	void CFrame::KeyHandle(int mcode)
	{
		switch(mcode)
		{
		case 1:
			{
				D3DXVECTOR3 v_vector;
				v_vector=m_lookat.operator-(m_eyePos);
				float sum,mag;
				sum=(v_vector.x*v_vector.x)+(v_vector.y*v_vector.y)+(v_vector.z*v_vector.z);
				mag=abs(sqrt(sum));
				v_vector.operator/=(mag);
				v_vector.operator*=(5.0);
				v_vector.y=0.0;
				m_eyePos.operator+=(v_vector);
				break;
				
			}
		case 2:
			{
				D3DXVECTOR3 v_vector;
				v_vector=m_lookat.operator-(m_eyePos);
				float sum,mag;
				sum=(v_vector.x*v_vector.x)+(v_vector.y*v_vector.y)+(v_vector.z*v_vector.z);
				mag=abs(sqrt(sum));
				v_vector.operator/=(mag);
				v_vector.operator*=(1.0);
				v_vector.y=0.0;
				m_eyePos.operator-=(v_vector);
				break;
			}
		}
	}

	