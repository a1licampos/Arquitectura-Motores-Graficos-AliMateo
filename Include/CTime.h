#pragma once
#include <Windows.h>

class 
CTime{
public:
	CTime();
	~CTime();

	/* Initialization QueryPerformanceCounter with m_iLastTime
	Initialiation QueryPerformanceFrequency with m_iTimerFrequency
	* 
	* QueryPerformanceCounter: Retrieves the current value of the performance counter, 
	* which is a high resolution (<1us) time stamp that can be used for time-interval 
	* measurements. 
	*
	* QueryPerformanceFrequency: Retrieves the frequency of the performance counter.
	* the frequency need only be queried upon application initialization, 
	* and the result can be cached.
	*/
	void 
	init();

	/* We get the current value of the performance counter with QueryPerformanceCounter
	* and save this value in m_iCurrentTime
	* Calculate deltaTime with operation bwtween currentTime & lastTime
	* Assign currentime to lastime
	* get min between deltatime and 0.1 because the data would be so little
	*/
	void 
	update();

	void 
	render();

	void 
	destroy();

private:
	//It's in charge to have the current time to initialize functions 
	//and make operations with deltatime
	LARGE_INTEGER m_iCurrentTime;
	//It's  charge to save the time before
	LARGE_INTEGER m_iLastTime;
	//Frequency of the performance counter
	LARGE_INTEGER m_iTimerFrequency;

public:
	//Time that use in the Tutorial7 to rotate and make operations
	float m_fDeltaTime;
};

