#pragma once

#define PI 3.141592f

#define MAKEFUNC(TYPE, NAME)\
private: TYPE m_##NAME;\
public: TYPE Get##NAME(){return m_##NAME;}\
void Set##NAME(TYPE value){m_##NAME = value;}