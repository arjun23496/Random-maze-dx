#include "CCube.h"

CCube::CCube()
{
	vno=0;
	primno=0;
	i_buffer=NULL;
	v_buffer=NULL;
}

void CCube::init_cube(LPDIRECT3DDEVICE9 d3ddev)
{
	

    // create the vertices using the CUSTOMVERTEX struct
    CUSTOMVERTEX vertices[] =
    {
        { -3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f,1,0 },    // side 1
        { 3.0f, -3.0f, 3.0f, 0.0f, 0.0f, 1.0f,1,1 },
        { -3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f,0,0 },
        { 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 1.0f,0,1 },

        { -3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f,1,0 },    // side 2
        { -3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f,1,1 },
        { 3.0f, -3.0f, -3.0f, 0.0f, 0.0f, -1.0f,0,0 },
        { 3.0f, 3.0f, -3.0f, 0.0f, 0.0f, -1.0f,0,1 },

        { -3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f,1,0 },    // side 3
        { -3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f,1,1 },
        { 3.0f, 3.0f, -3.0f, 0.0f, 1.0f, 0.0f,0,0 },
        { 3.0f, 3.0f, 3.0f, 0.0f, 1.0f, 0.0f,0,1 },

        { -3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f,1,0 },    // side 4
        { 3.0f, -3.0f, -3.0f, 0.0f, -1.0f, 0.0f,1,1 },
        { -3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f,0,0 },
        { 3.0f, -3.0f, 3.0f, 0.0f, -1.0f, 0.0f,0,1 },

        { 3.0f, -3.0f, -3.0f, 1.0f, 0.0f, 0.0f,1,0 },    // side 5
        { 3.0f, 3.0f, -3.0f, 1.0f, 0.0f, 0.0f,1,1 },
        { 3.0f, -3.0f, 3.0f, 1.0f, 0.0f, 0.0f,0,0 },
        { 3.0f, 3.0f, 3.0f, 1.0f, 0.0f, 0.0f,0,1 },

        { -3.0f, -3.0f, -3.0f, -1.0f, 0.0f, 0.0f,1,0 },    // side 6
        { -3.0f, -3.0f, 3.0f, -1.0f, 0.0f, 0.0f,1,1 },
        { -3.0f, 3.0f, -3.0f, -1.0f, 0.0f, 0.0f,0,0 },
        { -3.0f, 3.0f, 3.0f, -1.0f, 0.0f, 0.0f,0,1 },
    };

    // create a vertex buffer interface called v_buffer
    d3ddev->CreateVertexBuffer(24*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &v_buffer,
                               NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();

    // create the indices using an int array
    short indices[] =
    {
        0, 1, 2,    // side 1
        2, 1, 3,
        4, 5, 6,    // side 2
        6, 5, 7,
        8, 9, 10,    // side 3
        10, 9, 11,
        12, 13, 14,    // side 4
        14, 13, 15,
        16, 17, 18,    // side 5
        18, 17, 19,
        20, 21, 22,    // side 6
        22, 21, 23,
    };

	  // create an index buffer interface called i_buffer
    d3ddev->CreateIndexBuffer(36*sizeof(short),
                              0,
                              D3DFMT_INDEX16,
                              D3DPOOL_MANAGED,
                              &i_buffer,
                              NULL);

    // lock i_buffer and load the indices into it
    i_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, indices, sizeof(indices));
    i_buffer->Unlock();
}

int CCube::no_vertices()
{
	return 24;
}

int CCube::no_prim()
{
	return 12;
}

int CCube::size_vertexdata()
{
	return sizeof(CUSTOMVERTEX);
}

DWORD CCube::getFVF()
{
	return CUSTOMFVF;
}

LPDIRECT3DINDEXBUFFER9 CCube::get_ibuffer()
{
	return i_buffer;
}

LPDIRECT3DVERTEXBUFFER9 CCube::get_vbuffer()
{
	return v_buffer;
}