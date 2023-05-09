#include <iostream>
#include <string>
#include <vector>

template<typename Res, typename... Params>
struct IDelegate
{
public:
    virtual Res Invoke(Params... _params) const = 0;
};

template<typename Res, typename  Class, typename... Params>
struct MemberDelegate : public IDelegate<Res, Params...>
{
private:
    typedef Res(Class::*Function)(Params...); //ptr func
    Function function = nullptr;
    Class* owner = nullptr;

public:
    MemberDelegate(nullptr_t)
    {
        owner= nullptr;
        function= nullptr;
    }
    MemberDelegate(Class* _instance, Function _function)
    {
        owner = _instance;
        function = _function;
    }
    
    Res Invoke(Params... _params) const override
    {
        if(!IsValid())
            throw std::exception("[MemberDelegate] => function or owner null !");
        return (owner->*function)(_params...);
    }

    bool IsValid() const
    {
        return function != nullptr && owner != nullptr;
    }
    
    void SetDynamic(Class* _instance, Function _function)
    {
        owner = _instance;
        function = _function;
    }
    
    void operator =(Function _function)
    {
        function = _function;
    }
    void operator =(nullptr_t)
    {
        function = nullptr;
        owner = nullptr;
    }
};

template<typename Res, typename Class, typename... Params>
struct MemberDelegateConst : public IDelegate<Res, Params...>
{
private:
    typedef Res(Class::* Function)(Params...) const;
    Function function = nullptr;
    Class* owner = nullptr;
public:
    MemberDelegateConst(nullptr_t)
    {
        function = nullptr;
        owner = nullptr;
    }
    MemberDelegateConst(Class* _instance, Function _func)
    {
        owner = _instance;
        function = _func;
    }
    Res Invoke(Params... _params) const override
    {
        if(!IsValid())
            throw std::exception("[MemberDelegate] => function or owner null !");
        return (owner->*function)(_params...);
    }

    bool IsValid() const
    {
        return function != nullptr && owner != nullptr;
    }
    
    void SetDynamic(Class* _instance, Function _function)
    {
        owner = _instance;
        function = _function;
    }
    
    void operator =(Function _function)
    {
        function = _function;
    }

    void operator =(nullptr_t)
    {
        function = nullptr;
        owner = nullptr;
    }
    
};

template<typename Res, typename... Params>
class ActionInternal : public IDelegate<Res, Params...>
{
private:
    typedef std::vector<IDelegate<Res, Params...>*> DataType;
    DataType delegates = DataType();
public:
    ActionInternal(nullptr_t)
    {
        delegates = DataType();
    }
    

    template<typename Class>
    void AddDynamic(Class* _instance, Res(Class::*ptr)(Params...))
    {
        delegates.push_back(new MemberDelegate<Res, Class, Params...>(_instance, ptr));
        
    }
    template<typename Class>
    void AddDynamic(Class* _instance, Res(Class::*ptr)(Params...) const)
    {
        delegates.push_back(new MemberDelegateConst<Res, Class, Params...>(_instance, ptr));
        
    }

    Res Invoke(Params... _params) const override
    {
        const size_t _size = delegates.size();

        if constexpr (std::is_same_v<Res, void>) // => can do this in runtime
        {
            for (size_t i = 0; i < _size; ++i)
                delegates[i]->Invoke(_params...);
            return Res();
        }
        else //=> no runtime here
            {
            Res _result = Res();
            for (size_t i = 0; i < _size; ++i)
                _result = delegates[i]->Invoke(_params...);
            return _result;
            }
    }
};
template<typename... Params>
using Action = ActionInternal<void, Params...>;
