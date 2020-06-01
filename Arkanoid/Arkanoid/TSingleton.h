#pragma once
#include <Windows.h>

template <typename T>
class TSingleton
{
private:
	static T * m_pInstance;
//private:
protected:
	TSingleton(){}
	~TSingleton(){}
public:
	static T * GetInstance(HWND hWnd)
	{
		if (!m_pInstance)
		{
			m_pInstance = new T(hWnd);
		}
		return m_pInstance;
	}
};

template <typename T>
T * TSingleton<T>::m_pInstance = 0;