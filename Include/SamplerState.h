#pragma once
#include "Prerequisities.h"

//This is forward declaration from the (Device) class
class
Device;

class
DeviceContext;

class 
SamplerState{

public:
	SamplerState() = default;
	~SamplerState() {};

	/* Create the sample state, allow us to modify the dimensions of the texture
	* 
	* The sampler-state interface holds a description for sampler state that you can 
	* bind to any shader stage of the pipeline for reference by texture sample operations.
	* 
	* device: Reference to call method CreateSamplerState & can't be null
	*/
	void
	init(Device device);

	void
	update();

	void
	render(DeviceContext& deviceContext);

	/*
	* This function releases the pointer m_renderTargetView and sets it equal to NULL.
	*/
	void
	destroy();

public:
	//Address of a pointer to the sampler state object created
	ID3D11SamplerState* m_sampler = nullptr;

};
