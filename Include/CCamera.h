#pragma once
#include "Prerequisities.h"
#include "Commons.h"

class
Device;

class
DeviceContext;


class 
CCamera{
public:
	CCamera() = default;
	~CCamera() {};

	/* Initializes a camera on a specific graphics device. The camera will be used 
	* to render a scene in a 3D graphics program.
	* 
	* Device: Reference to call method CreateBuffer, 
	* if the creation is successful, the buffer is stored in the variable "m_camera"
	* 
	*/
	void
	init(Device device);


	/* The function Updates the data in the constant buffer for the camera. It does this by calling 
	* 
	* deviceContext: Reference to call method UpdateSubresource
	* 
	* Camera: This is in commons and has the matrix View and Projection
	*/
	void
	update(DeviceContext& deviceContext, Camera cam);


	/* The function sets the camera constant buffer as a vertex shader constant buffer 
	* by calling the "VSSetConstantBuffers" function of the device context object. 
	* 
	* deviceContext: Reference to call method VSSetConstantBuffers
	* 
	* This function is typically called once per frame to set up the camera data 
	* for rendering. By binding the camera constant buffer to the vertex shader stage, 
	* the camera data can be accessed by the vertex shader during the rendering process.
	*/
	void
	render(DeviceContext& deviceContext);

	// This function releases the pointer m_camera and sets it equal to NULL.
	void
	destroy();

public:
	ID3D11Buffer* m_camera = nullptr;

};
