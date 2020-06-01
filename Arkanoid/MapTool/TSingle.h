#pragma once

template <typename T>
class Singleton
{
private:
	static T * m_Instance;
protected:
	Singleton() {}
	~Singleton(){}
public:
	static T * GetInstance() 
	{ 
		if (!m_Instance)
		{
			m_Instance = new T;
			//m_Instance.Init();
		}
		return m_Instance;
	}
	static void DestoryInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}
	
	//virtual void Init() =0;
};

template <typename T>
T * Singleton<T>::m_Instance = 0;