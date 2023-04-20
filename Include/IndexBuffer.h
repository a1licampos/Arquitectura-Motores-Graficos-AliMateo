#pragma once
#include "Prerequisities.h"
#include "Commons.h"

class
Device;

class
DeviceContext;

class 
IndexBuffer{
public:
	IndexBuffer() = default;
	~IndexBuffer() {};

	/* The purpose of this function is to initialize the index buffer object, which 
	* is used to hold indices for the vertices of a 3D model.
	* 
	* The Device object represents the graphics device, and the LoadData object contains 
	* the data to be loaded into the index buffer.
	*/
	void
	init(Device device, LoadData loadData);

	void
	update();


	/* Sets the index buffer to the input assembler stage of the graphics pipeline 
	* using the IASetIndexBuffer() function of the DeviceContext object.
	* 
	*  DXGI_FORMAT_R32_UINT format which specifies that the indices are 32-bit unsigned integers
	*/
	void
	render(DeviceContext& deviceContext, unsigned int StartSlot);


	// This function releases the pointer m_indexBuffer and sets it equal to NULL.
	void
	destroy();

private:
	// The buffer is used to store the index data for rendering indexed primitives in Direct3D 11.
	ID3D11Buffer* m_indexBuffer = nullptr;
	unsigned int m_stride = sizeof(SimpleVertex);
};
