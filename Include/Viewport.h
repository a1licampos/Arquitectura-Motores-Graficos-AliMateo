#pragma once
#include "Prerequisities.h"

//This is forward declaration from the (Window) class
class
Window;

class
DeviceContext;

class 
Viewport{
public:
	Viewport() = default;
	~Viewport() {};

	//Create viewport and defines the dimensions of a viewport (width & height)
	void
	init(Window window);

	void
	update();

	void
	render(DeviceContext& deviceContext);

	void
	destroy();

public:
	//Defines the dimensions of a viewport.
	D3D11_VIEWPORT m_viewport;
};
