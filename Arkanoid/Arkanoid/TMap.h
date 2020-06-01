#pragma once
#include <map>
#include <list>
#include <iterator>
using namespace std;

template <typename KEY, typename VALUE>
class TMap
{
	map<KEY, VALUE> Tmap;
public:
	TMap();
	~TMap();

	bool Add(KEY key, VALUE value);
	bool GetValue(KEY key, VALUE &value);
	bool IsKey(KEY key);

	//Get
	map<KEY, VALUE> GetValues();
	list<VALUE> DicToList();

	int GetCount();

	void Remove(KEY key);
	void Clear();
	
	/*public VALUE this[KEY key]
	{
		get{
			return Tdic[key];
		}
			set{
			if (!IsKey(key)) {
				Debug.Log("Can't not find" + key.ToString());
				return;
			}
		Tdic[key] = value;
		}
	}*/
	
};
//template<typename KEY, typename VALUE>
// map<KEY, VALUE>::iterator M_ITER;


template<typename KEY, typename VALUE>
TMap<KEY, VALUE>::TMap()
{
	//Tmap = new map<KEY, VALUE>;
}

template<typename KEY, typename VALUE>
bool TMap<KEY, VALUE>::Add(KEY key, VALUE value)
{
	if (Tmap.at(key))
		return false;
	Tmap.insert(key, value);
	return true;
}

template<typename KEY, typename VALUE>
inline bool TMap<KEY, VALUE>::GetValue(KEY key, VALUE & value)
{
	if (Tmap.at(key))
	{
		value = Tmap[key];
		return true;
	}
	return false;
}

template<typename KEY, typename VALUE>
inline bool TMap<KEY, VALUE>::IsKey(KEY key)
{
	if (Tmap.at(key))
		return true;
	return false;
}

template<typename KEY, typename VALUE>
inline map<KEY, VALUE> TMap<KEY, VALUE>::GetValues()
{
	return Tmap;
}

template<typename KEY, typename VALUE>
list<VALUE> TMap<KEY, VALUE>::DicToList()
{
	list<VALUE> m_list = new list<VALUE>;

	
	for()


	return list<VALUE>();
}

template<typename KEY, typename VALUE>
int TMap<KEY, VALUE>::GetCount()
{
	return Tmap.count();
}

template<typename KEY, typename VALUE>
void TMap<KEY, VALUE>::Remove(KEY key)
{
	if (Tmap.at(key))
		Tmap.erase(key);
}

template<typename KEY, typename VALUE>
void TMap<KEY, VALUE>::Clear()
{
	Tmap.clear();
}
