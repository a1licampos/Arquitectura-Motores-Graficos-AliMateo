#include "CTime.h"

CTime::CTime(){
	m_iCurrentTime;
	m_iLastTime;
	m_iTimerFrequency;
}

CTime::~CTime(){
}

//Funciones de inicializacion
void 
CTime::init(){
	//Timer se ajuste a los frames de nuestra pantalla
	QueryPerformanceCounter(&m_iLastTime);
	QueryPerformanceFrequency(&m_iTimerFrequency);
}

void 
CTime::update(){

	//Lista del performance de nuestra computadora
	QueryPerformanceCounter(&m_iCurrentTime);	
	m_fDeltaTime = (m_iCurrentTime.QuadPart - m_iLastTime.QuadPart) / (float)m_iTimerFrequency.QuadPart;
	m_iLastTime = m_iCurrentTime;
	m_fDeltaTime = min(m_fDeltaTime, 0.1f);
}

void 
CTime::render(){
}

void 
CTime::destroy(){
}
