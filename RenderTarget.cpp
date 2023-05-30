#include "RenderTarget.h"

RenderTarget::RenderTarget(IDirect3DDevice9* dev)
{
	this->renTarDev = dev;
	this->renSurface = NULL;
	//this->renToSurface = NULL;
	this->renTexture = NULL;
	this->renTarget = NULL;
}

RenderTarget::~RenderTarget()
{
}

bool RenderTarget::createRenderTargetSurfaceAndTexture(UINT width, UINT height)
{
	bool bCreated = false;

	HRESULT hr = this->renTarDev->CreateRenderTarget(
		width, 
		height, 
		D3DFMT_A8R8G8B8, 
		D3DMULTISAMPLE_NONE, 
		0, 
		false, 
		&renTarget, 
		NULL);

	if (FAILED(hr)) {
		const char* error = DXGetErrorDescription(hr);
		MessageBox(NULL, error, "Could not create Render Target.", MB_OK);
		bCreated = false;
	}
	else
		bCreated = true;

	hr = renTarDev->CreateTexture(
		width, 
		height, 
		0, 
		D3DUSAGE_RENDERTARGET, 
		D3DFMT_A8R8G8B8, 
		D3DPOOL_DEFAULT, 
		&renTexture, 
		NULL);

	if (FAILED(hr)) {
		const char* error = DXGetErrorDescription(hr);
		MessageBox(NULL, error, "Could not create texture.", MB_OK);
		bCreated = false;
	}
	else
		bCreated = true;

	hr = renTexture->GetSurfaceLevel(0, &renSurface);
	if (FAILED(hr)) {
		const char* error = DXGetErrorDescription(hr);
		MessageBox(NULL, error, "Could not get surface level", MB_OK);
		bCreated = false;
	}
	return bCreated;
}

void RenderTarget::beginRenderTarget(UINT x, UINT y, UINT width, UINT height, DWORD ClearColor)
{
	D3DVIEWPORT9 viewPort;
	viewPort.X = x;
	viewPort.Y = y;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;

	this->renTarDev->SetViewport(&viewPort);
	this->renTarDev->SetRenderTarget(0, renSurface);
	this->renTarDev->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, ClearColor, 1.0f, 0);
	
	this->renTarDev->BeginScene();
	
//	this->renToSurface->BeginScene(renSurface, &viewPort);
}

void RenderTarget::endRenderTarget()
{
	this->renTarDev->EndScene();
	//this->renToSurface->EndScene(D3DX_FILTER_NONE);
	this->renTarDev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_LEFT, &renTarget);
	this->renTarDev->SetRenderTarget(0, renTarget);
}