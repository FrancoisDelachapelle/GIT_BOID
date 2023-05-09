#pragma once
#include <memory>

template<typename _type>
class Singleton
{
protected:
     static _type* instance = nullptr;
public :
    static _type* Instance();
};

template <typename _type>
_type* Singleton<_type>::Instance()
{
    if(instance == nullptr)
        instance = new _type;
    
    return instance;
}


