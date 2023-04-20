#pragma once
#include "Prerequisities.h"
#include "InputLayout.h"

class
Device;

class
DeviceContext;

class 
ShaderProgram{
public:
	ShaderProgram() = default;
	~ShaderProgram() {};

	/* Create Vertex, input and pixel shader (We call another functions in this same h)
	* 
	*  Set m_shaderFileName = fileName;
	*/
	void
	init(Device device,
			 std::string fileName,
			 std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

	void
	update();


	/* This function sets the shader program as the current shader program to be used 
	* during rendering.
	* 
	* deviceContext.IASetInputLayout: This specifies how the input data will be interpreted 
	* by the vertex shader.
	* 
	* deviceContext.VSSetShader: This specifies which vertex shader to use during rendering.
	* 
	* deviceContext.PSSetShader: specifies which pixel shader to use during rendering.
	*/
	void
	render(DeviceContext& deviceContext);


	/* This function releases the pointer m_VertexShader, m_PixelShader and sets 
	* it equal to NULL.
	*
	* Call function destroy m_inputLayout;
	*/
	void
	destroy();


	/* This is a method of the ShaderProgram class that compiles a shader from a file.
	* 
	* szFileName: a pointer to a string that specifies the name of the file that contains the shader code.
	*
	* szEntryPoint: a pointer to a string that specifies the entry point function of the shader.
	* 
	* szShaderModel: a pointer to a string that specifies the shader model version 
	* to compile the shader against.
	* 
	* ppBlobOut: a pointer to a pointer to an ID3DBlob interface that will be set to 
	*	the compiled shader code.
	*/
	HRESULT
	CompileShaderFromFile(const char* szFileName,
												LPCSTR szEntryPoint, 
												LPCSTR szShaderModel, 
												ID3DBlob** ppBlobOut);


	/* This function creates a vertex shader object using the CreateVertexShader 
	* method of the Device object passed as an argument.
	* 
	* Before creating the vertex shader, the function calls the CompileShaderFromFile 
	* method to compile the shader code from a file.
	*/
	void
	CreateVertexShader(Device device);


	/* This function creates an input layout for the shader program's vertex shader. 
	*
	* An input layout describes the format of the data that will be passed to the 
	* vertex shader as input.
	* 
	* The function takes as input a Device object and a vector of 
	* D3D11_INPUT_ELEMENT_DESC structures, which describe the layout of the input data.
	*/
	void
	CreateInputLayout(Device device, std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);


	/* This function is responsible for compiling and creating a pixel shader using the 
	* specified file name, entry point, and shader model.
	* 
	* the function creates a pixel shader using the "CreatePixelShader" function of the 
	* "Device" class. It passes the compiled pixel shader code, its buffer size, 
	* a null pointer for the class linkage interface, and a pointer to the variable 
	* "m_PixelShader".
	*/
	void
	CreatePixelShader(Device device);

	public:
		//Represents a vertex shader that can be used by the graphics processing unit (GPU) 
		//to process vertex data.
		ID3D11VertexShader* m_VertexShader = nullptr;

		//Represents a pixel shader that can be used by the GPU to process pixel data.
		ID3D11PixelShader* m_PixelShader = nullptr;

		//Encapsulates an input layout description for the vertex shader. 
		InputLayout m_inputLayout;

	private:
		std::string m_shaderFileName;
		ID3DBlob* m_vertexShaderData = nullptr;
		ID3DBlob* m_pixelShaderData = nullptr;

};
