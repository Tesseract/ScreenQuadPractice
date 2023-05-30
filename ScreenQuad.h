#pragma once

#include "D3DApp9.h"

struct Vector3
{
	Vector3()
		: x(0.0),
		  y(0.0),
		  z(0.0)
	{}

	Vector3(float x, float y, float z)
		: x(x),
		y(y),
		z(z)
	{

	}

	float x;
	float y;
	float z;
};

struct Vector2
{
	Vector2()
		: x(0.0),
		y(0.0) 
	{

	}

	Vector2(float x, float y) 
		: x(x),
		y(y)
	{}

	float x;
	float y;
};
struct VertexPTC
{
	VertexPTC()
	{
		position = Vector3(0.0f, 0.0f, 0.0f);
		texCoord = Vector2(0.0f, 0.0f);
		dwColor = 0x00000000;
	}

	VertexPTC(float x, float y, float z, float u, float v, DWORD color)
	{
		position = Vector3(x, y, z);
		texCoord = Vector2(u, v);
		dwColor = color;
	}

	Vector3 position;
	Vector2 texCoord;
	DWORD dwColor;

	size_t getPositionOffset() const { return 0; }

	size_t getTexCoordOffset() const { return sizeof(position); }

	size_t getColorOffSet() const { return sizeof(position) + sizeof(texCoord); }
};

/*struct
{
	type a;  // offset_a = 0
	type b;  // offset_b = offset_a + sizeof(a) + alignof(b) - ((offset_a + sizeof(a)) % alignof(b))  
	type c;  // offset_c = offset_b + sizeof(b) + alignof(c) - ((offset_b + sizeof(b)) % alignof(c))  
};*/

class ScreenQuad
{
protected:
	IDirect3DVertexDeclaration9* vertDecl;
	IDirect3DDevice9* quadDev;
	IDirect3DVertexBuffer9* vertBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	IDirect3DTexture9* texture;
	IDirect3DSurface9* renderSurface;
	VertexPTC* vertices;
	DWORD* indices;
	D3DVERTEXELEMENT9* vertElements;
public:
	ScreenQuad(IDirect3DDevice9* dev9);

	~ScreenQuad();

	void createScreenQuad();

	void renderScreenQuad();

	void setRenderTargetTexture(IDirect3DTexture9* tex);

	IDirect3DVertexBuffer9* getVertexBuffer() const { return this->vertBuffer; }

	VertexPTC* getVertices() const { return this->vertices; }
};