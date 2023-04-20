#pragma once
#include "Prerequisities.h"

//This is forward declaration from the (Device) class
class 
Device;

class 
InputLayout{

public:
	InputLayout() = default;
	~InputLayout() { SAFE_RELEASE(m_inputLayout) };

	/* Create an input-layout object to describe the input-buffer data 
	* for the input-assembler stage.
	* Layout can't be 0 & VertexShaderData can't be null
	* 
	* device: Reference to call method CreateInputLayout
	* 
	* Layout: An array of the input-assembler stage input data types; each type is 
	* described by an element description
	* 
	* VertexShaderData: Get buffer pointer and size
	*/
	void
	init(Device device,
	     std::vector<D3D11_INPUT_ELEMENT_DESC> Layout,
	     ID3DBlob* VertexShaderData);

	void 
	update();

	void 
	render();

	void 
	destroy();

public:
	/* An input-layout interface holds a definition of how to feed vertex data 
	* that is laid out in memory into the input-assembler stage of the graphics pipeline.
	*/
	ID3D11InputLayout* m_inputLayout = nullptr;

};
