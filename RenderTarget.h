#pragma once

#include "D3DApp9.h"
#include <iostream>

class RenderTarget
{
protected:
	IDirect3DDevice9* renTarDev;
	//ID3DXRenderToSurface* renToSurface;
	IDirect3DTexture9* renTexture;
	IDirect3DSurface9* renSurface;
	IDirect3DSurface9* renTarget;
public:
	RenderTarget(IDirect3DDevice9* dev);

	~RenderTarget();

	bool createRenderTargetSurfaceAndTexture(UINT width, UINT height);

	void beginRenderTarget(UINT x, UINT y, UINT width, UINT height, DWORD ClearColor);

	void endRenderTarget();

	IDirect3DTexture9* getTexture() const { return renTexture; }

	//ID3DXRenderToSurface* getRenderToSurface() const { return this->renToSurface; }
};