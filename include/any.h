// 目标：实现一个支持 json 序列化/反序列化、支持 std::cout 输出的 any 类型
// 要求：基于 C++11/C++14，采用 json 序列化库 Tencent/rapidjson
#include <memory>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <algorithm>
#include "reflection.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

enum class Type
{
    tint,
    tbool,
    tdouble,
    tstring,
    tobject,
    tarray
};

std::map<std::string, Type> types = {{"int", tint},
                                     {"bool", tbool},
                                     {"double", tdouble},
                                     {"string", tstring},
                                     {"object", tobject},
                                     {"array", tarray}};

class Any
{
    friend std::ostream &operator<<(std::ostream &o, const Any &a);
public:
    Any()
    {
        // setup converter (partial)
        auto int_converter = [](int* field, const std::string& name) {
          std::cout << name << ": " << *field << std::endl;
        };
        auto string_converter = [](std::string* field, const std::string& name) {
          std::cout << name << ": " << *field << std::endl;
        };
        auto double_converter = [](double* field, const std::string& name) {
          std::cout << name << ": " << *field << std::endl;
        };
        auto bool_converter = [](bool* field, const std::string& name) {
          std::cout << name << ": " << *field << std::endl;
        };
        auto bool_converter = [](bool* field, const std::string& name) {
          std::cout << name << ": " << *field << std::endl;
        };

        converter.RegisterField(&SimpleStruct::int_, "int",
                                ValueConverter<int>(int_converter));
        converter.RegisterField(&SimpleStruct::string_, "string",
                                ValueConverter<std::string>(string_converter));
        converter.RegisterField(&SimpleStruct::bool_, "bool",
                                ValueConverter<bool>(bool_converter));
        converter.RegisterField(&SimpleStruct::double_, "double",
                                ValueConverter<double>(double_converter));
        converter.RegisterField(&NestedStruct::nested_, "object",
                                ValueConverter<SimpleStruct>(object_converter));
    }
    Any(const Any &other) : Any()
    {
        base = other.base->clone();
    }
    Any(Any &&other): base(other.base)
    {
    }

    template <typename T>
    Any(const T &t) : base(new Data<T>(t))
    {
    }
    template <typename T>
    Any(T &&t) : base(new Data<T>(t))
    {
    }
    template <typename T>
    T any_cast()
    {
        return dynamic_cast<Data<T>*>(base.get())->value;
    }

    Any &operator=(const Any &other)
    {
        Any(other).swap(*this);
        return *this;
    }
    Any &operator=(Any &&other)
    {
        std::swap(base, other.base);
        return *this;
    }
    template <typename T>
    Any &operator=(T &&t)
    {
        Any(t).swap(*this);
        return *this;
    }
    template <typename T>
    Any &operator=(const T &t)
    {
        Any(t).swap(*this);
        return *this;
    }

    bool operator==(const Any &other)
    {
        return true;
    }
    bool operator==(Any &&other)
    {
        return true;
    }

    Any &swap(Any &other)
    {
        std::swap(base, other.base);
        return *this;
    }

    std::string dump() const
    {
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        
        writer.StartObject();
        
        string data = strBuf.GetString();
        Type t = base->get_type();
        int i_value = 0;
        double d_value = 0.0;
        bool b_value = true;
        std::string s_value;

        std::string key;
        writer.Key(key);
        switch (t)
        {
        case Type::tint:
            writer.Int();
        case Type::tdouble:
            writer.Double();
        case Type::tbool:
            writer.Bool();
        case Type::tstring:
            writer.String();
        case Type::tarray:
            writer.StartArray();
            writer.EndArray();
        case Type::tobject:
            writer.StartObject();
            writer.EndObject();
        }

        writer.EndObject();

        return buffer.GetString();
    }

private:
    class Base
    {
    public:
        virtual ~Base() {}
        virtual Base *clone() {}
        virutal Type get_type() {}
    };
    template <typename T>
    class Data : public Base
    {
    public:
        Data(const T &t) : value(t)
        {}
        Data(T &&t) : value(t)
        {}

        Base *clone()
        {
            T *r = new T(value);
            return r;
        }
        Type get_type()
        {
            return types[typeid(value).name()];
        }

        bool operator==(const T &v)
        {
            return value == v.value;
        }

        friend std::ostream &operator<<(std::ostream &o, const T &t);

        T value;
    };

private:
    std::unique_ptr<Base> base;

    rapidjson::StringBuffer buffer;
    StructValueConverter<SimpleStruct> converter;
};

std::ostream &operator<<(std::ostream &o, const T &t)
{
   o << t;
   return o;
}

std::ostream &operator<<(std::ostream &o, const Any &a)
{
    o << dynamic_cast<Data<T>*>(a.base.get())->value;
    return o;
}
