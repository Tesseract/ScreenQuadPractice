#include <iostream>
#include "D3DApp9.h"
#include "ScreenQuad.h"
#include "RenderTarget.h"
#include <exception>
using std::cout;
using std::endl;

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND CreateRenderWindow(const char* title, UINT width, UINT height);

#define TANYA L"Tanya.jpeg";
int main()
{
	try {

		HWND hWnd = CreateRenderWindow("Screen_Quad", 800, 600);
		D3DApp9* d3d9 = new D3DApp9();
		d3d9->createDirect3D9(hWnd, 800, 600, false);
		if (hWnd)
		{
			ShowWindow(hWnd, SW_SHOW);
			UpdateWindow(hWnd);
		}

		ScreenQuad* quad = new ScreenQuad(d3d9->getD3DDevice9());
		quad->createScreenQuad();
		RenderTarget* target = new RenderTarget(d3d9->getD3DDevice9());

		if (target->createRenderTargetSurfaceAndTexture(256, 256))
		{
			cout << "Render Target created" << endl;
		}

		IDirect3DTexture9* tanya = NULL;
		ID3DXMesh* cube = NULL;
		D3DXCreateTextureFromFile(d3d9->getD3DDevice9(), "Tanya.jpeg", &tanya);
		D3DXCreateBox(d3d9->getD3DDevice9(), 20.0f, 20.0f, 20.0f, &cube, NULL);
		d3d9->addInterface(tanya);
		d3d9->addInterface(cube);
		//d3d9->addInterface();

		cout << "Max primitive count: " << d3d9->getMaxPrimitiveCount() << endl;
		MSG msg;
		bool running = true;
		while (running)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT)
				{
					running = false;
				}
			}
			target->beginRenderTarget(0, 0, 800, 600, D3DCOLOR_ARGB(255, 0, 0, 0));

/*			D3DXMATRIX pView;
			D3DXMATRIX pProjection;
			D3DXMATRIX pTranslation;
			D3DXMatrixIdentity(&pView);
			D3DXMatrixIdentity(&pProjection);
			D3DXMatrixIdentity(&pTranslation);
			D3DXVECTOR3 eye(0.0f, 0.0f, -100.0f);
			D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXMatrixLookAtLH(&pView,
				&eye, &at, &up);
			d3d9->getD3DDevice9()->SetTransform(D3DTS_VIEW, &pView);
			D3DXMatrixPerspectiveFovLH(&pProjection, 45.0f, (float)(800 / 600), 1.0f, 1000.0f);
			d3d9->getD3DDevice9()->SetTransform(D3DTS_PROJECTION, &pProjection);
			D3DXMatrixTranslation(&pTranslation, 0.0f, 0.0f, 0.0f);
			d3d9->getD3DDevice9()->SetTransform(D3DTS_WORLD, &pTranslation);
			d3d9->getD3DDevice9()->SetRenderState(D3DRS_LIGHTING, FALSE);
			cube->DrawSubset(0);*/
			


			target->endRenderTarget();
			quad->setRenderTargetTexture(target->getTexture());
			//quad->setRenderTargetTexture(tanya);
			d3d9->clear(255, 100, 0, 255);
			d3d9->begin();
			D3DXMATRIX pView;
			D3DXMATRIX pProjection;
			D3DXMATRIX pTranslation;
			D3DXMatrixIdentity(&pView);
			D3DXMatrixIdentity(&pProjection);
			D3DXMatrixIdentity(&pTranslation);
			D3DXVECTOR3 eye(0.0f, 0.0f, -100.0f);
			D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
			D3DXMatrixLookAtLH(&pView,
				&eye, &at, &up);
			d3d9->getD3DDevice9()->SetTransform(D3DTS_VIEW, &pView);
			D3DXMatrixPerspectiveFovLH(&pProjection, 75.0f, (float)(800 / 600), 1.0f, 1000.0f);
			d3d9->getD3DDevice9()->SetTransform(D3DTS_PROJECTION, &pProjection);
			D3DXMatrixTranslation(&pTranslation, 0.0f, 0.0f, 0.0f);
			d3d9->getD3DDevice9()->SetTransform(D3DTS_WORLD, &pTranslation);
			d3d9->getD3DDevice9()->SetRenderState(D3DRS_LIGHTING, FALSE);
			cube->DrawSubset(0);
			D3DXMATRIX twoD;
			D3DXMATRIX twoDP;
			D3DXMatrixIdentity(&twoD);
			D3DXMatrixIdentity(&twoDP);
			d3d9->getD3DDevice9()->SetTransform(D3DTS_VIEW, &twoD);
			d3d9->getD3DDevice9()->SetTransform(D3DTS_PROJECTION, &twoDP);
			quad->renderScreenQuad();
			d3d9->end();
			d3d9->present();
		}
		
		delete d3d9;
		d3d9 = 0;
	}
	catch (std::exception& e)
	{
		MessageBox(NULL, e.what(), "Exception", MB_OK);
	}
	return EXIT_SUCCESS;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_QUIT:
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND CreateRenderWindow(const char* title, UINT width, UINT height)
{
	WNDCLASSEX winClassEx;
	ZeroMemory(&winClassEx, sizeof(WNDCLASSEX));

	winClassEx.cbSize = sizeof(WNDCLASSEX);

	winClassEx.style = CS_HREDRAW | CS_VREDRAW;
	winClassEx.lpfnWndProc = WinProc;
	winClassEx.hInstance = GetModuleHandle(NULL);
	winClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClassEx.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winClassEx.lpszClassName = title;

	if (!RegisterClassEx(&winClassEx))
	{
		MessageBox(NULL, "Could not register window", "Error", MB_OK | MB_ICONINFORMATION);
		return NULL;
	}

	return CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		title, title,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		width,
		height,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);
}
