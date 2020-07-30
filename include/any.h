#include <memory>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <algorithm>

class Any
{
// friend std::ostream &operator<<(std::ostream &o, const Any &a);
public:
    Any()
    {
    }
    Any(const Any &other)
    {
        if (other.base)
        {
            base.reset(other.base->clone());
        }
        printf("call Any(const Any &other)\n");
    }
    Any(Any &&other): base(std::move(other.base))
    {
        other.base.reset(nullptr);
        printf("call Any(Any &&other)\n");
    }
    template <typename T>
    Any(const T &t) : base(new Data<std::decay_t<T>>(t))
    {
        printf("call const T &\n");
    }
    template <typename T>
    Any(T &&t,
        std::enable_if_t<!std::is_same<Any&, T>::value>* = 0, // disable if T has type Any&
        std::enable_if_t<!std::is_const<T>::value>* = 0)    // disable if T has const T&&
        : base(new Data<std::decay_t<T>>(std::forward<T>(t)))
    {
        printf("call T &&\n");
    }
    template <typename T>
    T cast()
    {
        return dynamic_cast<Data<T>*>(base.get())->value;
    }

    Any &operator=(const Any &other)
    {
        printf("operator=(const Any&)\n");
        Any(other).swap(*this);
        return *this;
    }
    Any &operator=(Any &&other)
    {
        printf("operator=(Any&&)\n");
        std::swap(base, other.base);
        return *this;
    }
    template <typename T>
    Any &operator=(T &&t)
    {
        printf("operator=(T&&)\n");
        Any(std::forward<T>(t)).swap(*this);
        return *this;
    }
    template <typename T>
    Any &operator=(const T &t)
    {
        printf("operator=(const T&)\n");
        Any(t).swap(*this);
        return *this;
    }

    Any &swap(Any &other)
    {
        std::swap(base, other.base);
        return *this;
    }

    std::string dump() const
    {
        return "";
    }

    bool empty() const
    {
        return !base;
    }

    const std::type_info &type() const
    {
        return base ? base->type() : typeid(void);
    }

private:
    class Base
    {
    public:
        virtual ~Base() {}
        virtual Base *clone() const = 0;
        virtual const std::type_info &type() const = 0;
    };
    template <typename T>
    class Data : public Base
    {
    public:
        Data(const T &t) : value(t)
        {}
        Data(T &&t) : value(std::move(t))
        {}
        virtual ~Data()
        {}

        Base *clone() const override
        {
            return new Data(value);
        }
        const std::type_info &type() const override
        {
            return typeid(T);
        }

        T value;
    };

private:
    std::unique_ptr<Base> base;
};

/*
std::ostream &operator<<(std::ostream &o, const Any &a)
{
    if (a->type().hash_code() == typeid(int).hash_code())
    {
        return o << a.cast<int>();
    }
    else if (a->type().hash_code() == typeid(float).hash_code())
    {
        return o << a.cast<float>();
    }
}
*/
