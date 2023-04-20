#pragma once
#include "Prerequisities.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <imgui_internal.h>


class 
UserInterface{
public:
	UserInterface() = default;
	~UserInterface() {};

	/* https://github.com/ocornut/imgui
	* 
	* An IMGUI tries to minimize superfluous state duplication, state 
	* synchronization, and state retention from the user's point of view. 
	* 
	* Dear ImGui outputs vertex buffers and command lists that you can easily render 
	* in your application. The number of draw calls and state changes required to render 
	* them is fairly small. Because Dear ImGui doesn't know or touch graphics state directly
	* 
	*/
	void 
	init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	void 
	update();

	void 
	render();

	void 
	destroy();

	/* Create a 3 colum to modify the values, in this case, x, y and z transform mode
	* We can put a reset values when we push the button o modify colum size
	*/
	void
	vec3Control(std::string label, 
							float* values, 
							float resetValues = 0.0f, 
							float columWidth = 100.0f);
	
	// This function modify the Imgui style
	void 
	embraceTheDarkness();

};

