#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>
#include <stack>

typedef std::stack<IUnknown*> Interfaces;

#pragma comment(lib, "d3d9.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "d3dx9d.lib")
#pragma comment(lib, "dxerr.lib")
#elif
#pragma comment(lib, "d3dx9.lib")
#endif

#define RELEASE_INTERFACE(x) {if(x){x->Release(); x = 0; }}

class D3DApp9
{
protected:
	IDirect3D9* d3d9;
	IDirect3DDevice9* d3dDev9;
	D3DPRESENT_PARAMETERS present_parameters;
	D3DCAPS9 d3dCaps9;
	Interfaces interfaces;
public:
	D3DApp9();

	~D3DApp9();

	bool createDirect3D9(HWND hwnd, unsigned int width, unsigned int height, bool fullScreen);

	void clear(BYTE a, BYTE r, BYTE g, BYTE b);

	void begin();

	void end();

	void present();

	void addInterface(IUnknown* inter);

	IDirect3D9* getD3D9() const { return d3d9; }

	IDirect3DDevice9* getD3DDevice9()const { return d3dDev9; }

	DWORD getMaxPrimitiveCount() const { return this->d3dCaps9.MaxPrimitiveCount; }
};