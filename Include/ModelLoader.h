#pragma once
#include "Prerequisities.h"
#include "Commons.h"

class ModelLoader
{
public:
	ModelLoader() = default;
	~ModelLoader() {};

	void
	init();

	void
	update();

	void
	render();

	void
	destroy();

	/* Extract de vertex pos and text to load any model
	* Only need the name of the file to load this.
	* 
	* We create this function Chat GPT help
	*/
	LoadData
	load(std::string objFileName);


};
