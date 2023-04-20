#pragma once
#include "Prerequisities.h" 

class 
Device{
public:
	Device() = default;
	~Device() { SAFE_RELEASE(m_device) };

	void
	init();

	void
	update();

	void
	render();

	/*
	* This function releases the pointer m_renderTargetView and sets it equal to NULL.
	*/
	void
	destroy();

	//Create a depth-stencil view for accessing resource data.
	HRESULT
	CreateDepthStencilView(ID3D11Resource* pResource, 
			       const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc, 
			       ID3D11DepthStencilView** ppDepthStencilView);

	//Creates a render-target view for accessing resource data.
	HRESULT
	CreateRenderTargetView(ID3D11Resource* pResource,
			       const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
			       ID3D11RenderTargetView** ppRTView);

	//Creates a resource that stores information that is used in texture
	HRESULT
	CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
                  	const D3D11_SUBRESOURCE_DATA *pInitialData,
                  	ID3D11Texture2D** ppTexture2D);

	//Create a vertex-shader object from a compiled shader.
	HRESULT
	CreateVertexShader(const void* pShaderBytecode,
			   unsigned int BytecodeLength,
			   ID3D11ClassLinkage* pClassLinkage, 
			   ID3D11VertexShader** ppVertexShader);

	//Create an input-layout object to describe the input-buffer data for the 
	//input-assembler stage.
	HRESULT
	CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
			  unsigned int NumElements,
			  const void *pShaderBytecodeWithInputSignature,
			  unsigned int BytecodeLength, 
			  ID3D11InputLayout** ppInputLayout);

	//Create a pixel shader.
	HRESULT
	CreatePixelShader(const void* pShaderBytecode,
			  unsigned int BytecodeLength,
			  ID3D11ClassLinkage *pClassLinkage,
			  ID3D11PixelShader** ppPixelShader);

	//Creates a buffer (vertex buffer, index buffer, or shader-constant buffer).
	HRESULT
	CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
		     const D3D11_SUBRESOURCE_DATA* pInitialData,
		     ID3D11Buffer** ppBuffer);

	//Create a sampler-state object that encapsulates sampling information for a texture.
	HRESULT
	CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
			   ID3D11SamplerState **ppSamplerState);

public:
	//The device interface represents a virtual adapter; it is used to create resources.
	ID3D11Device* m_device = nullptr;

};

