#pragma once
#include "Prerequisities.h"

//This is forward declaration from the (Device) class
class
Device;

//This is forward declaration from the (DeviceContext) class
class
DeviceContext;

//This is forward declaration from the (Window) class
class
Window;

//This is forward declaration from the (Texture) class
class
Texture;

class SwapChain{

public:
	SwapChain() = default;
	~SwapChain() {};

	/* Create Direct3D device, device Context and gives contextualization to backbuffer
	* Swap chains control the back buffer rotation, forming the basis of graphics animation.
	* 
	* window: can't be null, to get width, height and m_hWnd
	* 
	* device: to have reference/access a  m_device
	* 
	* deviceContext: to have reference/access a  m_deviceContext
	* 
	* backBuffer: to have reference/access a  m_texture
	*/
	void
	init(Device& device,
	     DeviceContext& deviceContext,
	     Texture& backBuffer,
	     Window window);

	void 
	update();

	void
	render();

	/*
	* This function releases the pointer m_renderTargetView and sets it equal to NULL.
	*/
	void
	destroy();

	/* 
	* This is a method in charge of presenting the information on the screen
	*/
	void
	present();


public:
	//The D3D_DRIVER_TYPE, which represents the driver type to create.
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

	//Returns a pointer to a D3D_FEATURE_LEVEL, which represents the first element 
	//in an array of feature levels supported by the device.
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

	//Returns the address of a pointer to the IDXGISwapChain object that represents 
	//the swap chain used for rendering.
	IDXGISwapChain* m_swapChain = nullptr;

};
