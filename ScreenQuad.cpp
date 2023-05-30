#include "ScreenQuad.h"

ScreenQuad::ScreenQuad(IDirect3DDevice9* dev)
{
	this->quadDev = dev;
	this->vertBuffer = NULL;
	this->indexBuffer = NULL;
	this->indices = 0;
	this->vertices = NULL;
	this->renderSurface = NULL;
	this->texture = NULL;
	this->vertDecl = NULL;
	this->vertElements = new D3DVERTEXELEMENT9[63];
}

ScreenQuad::~ScreenQuad()
{
	RELEASE_INTERFACE(vertDecl);
	delete[] vertElements;
	vertElements = 0;
	RELEASE_INTERFACE(vertBuffer);
	delete[] vertices;
	vertices = 0;
}

void ScreenQuad::setRenderTargetTexture(IDirect3DTexture9* tex)
{
	this->texture = tex;
}

void ScreenQuad::createScreenQuad()
{
	
	quadDev->CreateVertexBuffer(4 * sizeof(VertexPTC), D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &vertBuffer, NULL);

	vertBuffer->Lock(0, 0, (void**)&this->vertices, 0);
	
	vertices[0] = VertexPTC(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255));
	vertices[1] = VertexPTC(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255));
	vertices[2] = VertexPTC(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 255));
	vertices[3] = VertexPTC(1.0f, 0.0f, 1.0f, 1.0f, 1.0f, D3DCOLOR_ARGB(255, 255, 255, 255));


	vertBuffer->Unlock();
	
	D3DVERTEXELEMENT9 elem[] = {
			{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
			{0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
			{0, 20, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,0},
			D3DDECL_END()
	};
	
	this->vertElements = elem;
	quadDev->CreateVertexDeclaration(vertElements, &vertDecl);

/*	HRESULT hr = quadDev->CreateIndexBuffer(6 * sizeof(VertexPTC), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &indexBuffer, NULL);

	if (FAILED(hr))
	{
		const char* error = DXGetErrorDescription(hr);
		MessageBox(NULL, error, "Could not create index buffer", MB_OK);
	}

	indexBuffer->Lock(0, 0, (void**)&this->indices, 0);

	DWORD k = 0;
	for (DWORD i = 0; i < 6; i++)
	{
		for (DWORD j = 0; j < 6; j++)
		{
			indices[k] = i * 3 + j;
			indices[k + 1] = i * 3 + j + 1;
			indices[k + 2] = (i + 1) * 3 + j;

			indices[k + 3] = (i + 1) * 3 + j;
			indices[k + 4] = i * 3 + j + 1;
			indices[k + 5] = (i + 1) * 3 + j + 1;

			k += 6;
		}
	}

	indexBuffer->Unlock();*/
}

void ScreenQuad::renderScreenQuad()
{
	//this->quadDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	this->quadDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	this->quadDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	this->quadDev->SetVertexDeclaration(vertDecl);
	this->quadDev->SetStreamSource(0, vertBuffer, 0, sizeof(VertexPTC));
	if (this->texture) {
		this->quadDev->SetTexture(0, texture);
	}
	else {
		this->quadDev->SetTexture(0, NULL);
	}
//	this->quadDev->SetIndices(this->indexBuffer);
//	this->quadDev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 6, 0, 2);
	this->quadDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}