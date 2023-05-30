#include "D3DApp9.h"

D3DApp9::D3DApp9()
{
	this->d3d9 = NULL;
	this->d3dDev9 = NULL;
	this->present_parameters = {};
}

D3DApp9::~D3DApp9()
{
	while (!interfaces.empty())
	{
		IUnknown* i = interfaces.top();
		RELEASE_INTERFACE(i);
		interfaces.pop();
	}
}

void D3DApp9::addInterface(IUnknown* inter)
{
	interfaces.push(inter);
}

bool D3DApp9::createDirect3D9(HWND hwnd, unsigned int width, unsigned int height, bool fullScreen)
{
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	if (d3d9 == NULL)
	{
		throw "Direct3D Could not be created";
	}
	else
	{
		interfaces.push(d3d9);
	}

	ZeroMemory(&this->present_parameters, sizeof(D3DPRESENT_PARAMETERS));
	this->present_parameters.BackBufferCount = 1;
	this->present_parameters.BackBufferWidth = width;
	this->present_parameters.BackBufferHeight = height;
	this->present_parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	this->present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->present_parameters.Windowed = (!fullScreen);
	this->present_parameters.EnableAutoDepthStencil = TRUE;
	this->present_parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	this->present_parameters.hDeviceWindow = hwnd;

	HRESULT hr = d3d9->CreateDevice(0,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&this->present_parameters,
		&d3dDev9);

	if (FAILED(hr))
	{
		const char* error = DXGetErrorDescription(hr);
		throw error;
		return false;
	}
	else
	{
		interfaces.push(d3dDev9);
		d3dDev9->GetDeviceCaps(&this->d3dCaps9);
		return true;
	}
	return true;
}

void D3DApp9::clear(BYTE a, BYTE r, BYTE g, BYTE b)
{
	d3dDev9->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(a, r, g, b), 1.0f, 1);
}

void D3DApp9::begin()
{
	d3dDev9->BeginScene();
}

void D3DApp9::end()
{
	d3dDev9->EndScene();
}

void D3DApp9::present()
{
	d3dDev9->Present(0, 0, 0, 0);
}