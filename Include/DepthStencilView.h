#pragma once
#include "Prerequisities.h"

//This is forward declaration from the (Device) class
class 
Device;

class
DeviceContext;

class 
DepthStencilView{
public:
	DepthStencilView() = default;
	~DepthStencilView(){SAFE_RELEASE(m_pDepthStencilView) };

	/*Create the depth stencil view for accessing resource data.
	* device & depthStencil can't be null		
	* 
	*	device: Pointer to the resource that will serve as the depth-stencil surface
	* 
	* depthStencil: Pointer to a depth-stencil-view description
	* 
	* Format: Resource data formats
	*/
	void
	init(Device device, 
	     ID3D11Resource* depthStencil, 
	     DXGI_FORMAT Format);

	void
	update();

	void
	render(DeviceContext& deviceContext);

	/*CHECK OUT: it's making a breakpoint error (WARNING)
	* 
	* This function releases the pointer m_pDepthStencilView and sets it equal to NULL.
	*/
	void
	destroy();

public:
	/*This a reference about the same class
	* 
	* Address of a pointer to an ID3D11DepthStencilView. 
	* Set this parameter to NULL to validate the other input parameters
	*/
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;

};

