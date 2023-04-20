#pragma once
#include "Prerequisities.h"
#include "Commons.h"

class
Device;

class
DeviceContext;

class 
VertexBuffer{
public:
	VertexBuffer() = default;
	~VertexBuffer() {};

	/* This code initializes a vertex buffer object (VBO) in Direct3D 11. The VBO is used 
	* to store vertex data for rendering geometry in a graphics pipeline.
	* 
	* The function then sets up a D3D11_SUBRESOURCE_DATA object, which contains a pointer 
	* to the vertex data to be stored in the buffer. It calls the CreateBuffer
	* function of the Device object to create the buffer, passing in the buffer 
	* description and initialization data.  
	*/
	void
	init(Device device, LoadData loadData);

	void
	update();


	/* sets the vertex buffer to the input assembler stage of the graphics pipeline 
	* using the IASetVertexBuffers function of the DeviceContext class.
	* 
	* StartSlot: specifies the first input slot for binding the vertex buffer. In this case, 
	* we bind only one vertex buffer, so we set the count parameter to 1. 
	*/
	void
	render(DeviceContext& deviceContext, unsigned int StartSlot);

	//This function releases the pointer m_vertexBuffer and sets it equal to NULL.
	void
	destroy();

private:
	// Is a pointer to the actual vertex buffer resource created in GPU memory.
	ID3D11Buffer* m_vertexBuffer = nullptr;

	// Is the size (in bytes) of each vertex in the buffer. 
	//In this case, it is set to the size of the SimpleVertex struct.
	unsigned int m_stride = sizeof(SimpleVertex);

	// Is the offset (in bytes) from the beginning of the buffer where vertex data starts. 
	unsigned int m_offset = 0;
};
