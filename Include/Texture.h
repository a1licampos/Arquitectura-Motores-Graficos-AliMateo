#pragma once
#include "Prerequisities.h"
#include "Commons.h"

//This is forward declaration from the (Device) class
class 
Device;

class
DeviceContext;

class 
Texture{

public:
	Texture() = default;
	~Texture() {};

	/* 
	* Initialize texture from the file
	* 
	* device: to get reference m_device and can't be null
	* 
	* textureName: to get the file's name
	*/
	void
	init(Device device, 
	     std::string textureName);

	/*
	* Initialize texture from the resource
	* Create an array of 2D texture
	* 
	* device: to get reference m_device, can't be null and reference 
	* to call method CreateTexture2D
	*/
	void
	init(Device device,
	     unsigned int width,
	     unsigned int height,
	     DXGI_FORMAT Format,
	     unsigned int BindFlags);

	void
	update();

	void 
	render(DeviceContext& deviceContext);

	void 
	destroy();


public:
	//This variable is in charge if handle a texture resource as data
	ID3D11Texture2D* m_texture = nullptr;

	//This variable is in charge of hanlde a texture resource as image data
	ID3D11ShaderResourceView* m_textureFromImg = nullptr;

};

