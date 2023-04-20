#pragma once
#include <Windows.h>

class 
Window{
public:
	Window();
	~Window();

	/* Method to creating/showing window
	* 
	* hInstance: is the handle to an instance or handle to a module. 
	* 
	* nCmdShow: The nCmdShow parameter can be used to minimize or maximize a window. 
	* 
	* wndproc:  is a pointer to an application-defined function called the window 
	* procedure or window proc. The window procedure defines most of the 
	* behavior of the window. 
	* 
	* windowName:	is a string that identifies the window class.
	*/
	HRESULT 
	init(HINSTANCE hInstance, 
	     int nCmdShow, 
	     WNDPROC wndproc, 
	     LPCSTR windowName);

	void
	update();

	void
	render();

	void 
	destroy();


public:
	//The hwnd parameter is the window handle returned by CreateWindowEx.
	HWND m_hWnd = nullptr;

	//hInstance in WNDCLASSEX specifies the instance under which the class is registered.
	HINSTANCE m_hInst = nullptr;

	/*A pointer to a RECT structure that receives the client coordinates. The left 
	* and top members are zero. The right and bottom members contain the width 
	* and height of the window.
	*/
	RECT m_rect;

	//get the window width
	unsigned int m_width;

	//get the window height
	unsigned int m_height;

	//get the window name
	LPCSTR m_windowName = "None";
};

