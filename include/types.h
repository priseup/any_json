#include <iostream>
#include <tuple>
#include <vector>
#include <string>

enum class Type : unsigned char
{
    NONE = 0,
    BOOLEAN,
    INTEGER,
    DOUBLE,
    STRING,
    ARRAY,
    OBJECT
};

/*
std::map<std::string, Type> types = {{"int", Type::tint},
                                     {"bool", Type::tbool},
                                     {"double", Type::tdouble},
                                     {"string", Type::tstring},
                                     {"object", Type::tobject},
                                     {"array", Type::tarray}};
                                     */

struct Person;

struct Singer {
    friend std::ostream &operator<<(std::ostream &o, const Singer &s);

    std::string type;
    int age;

    bool operator==(const Singer &s) const
    {
        return std::tie(type, age) == std::tie(s.type, s.age);
    }
};

struct Address {
    friend std::ostream &operator<<(std::ostream &o, const Address &a);

    std::string country;
    std::string city;
    std::string street;
    std::vector<Person> neighbors;

    bool operator==(const Address &a) const
    {
        return std::tie(country, city, street) == std::tie(a.country, a.city, a.street)
                && neighbors == a.neighbors;
    }
};

struct Friend {
    friend std::ostream &operator<<(std::ostream &o, const Friend &f);

    std::string relation;
    Any secret;

    bool operator==(const Friend &f) const
    {
        return std::tie(relation, secret) == std::tie(f.relation, f.secret);
    }
};

struct Person {
    friend std::ostream &operator<<(std::ostream &o, const Person &p);

    std::string name;
    int age;
    Address address;
    std::vector<Friend> _friends;
    Any secret;

    bool operator==(const Person &p) const
    {
        return std::tie(name, age, address, secret) == std::tie(p.name, p.age, p.address, p.secret)
                && _friends == p._friends;
    }
};

std::ostream &operator<<(std::ostream &o, const Singer &s)
{
    o << s.type << ", " << s.age;
    return o;
}

std::ostream &operator<<(std::ostream &o, const Address &a)
{
    o << a.country << ", " << a.city << ", " << a.street << ", ";
    std::copy(begin(a.neighbors), end(a.neighbors), std::ostream_iterator<Person>(o, "| "));

    return o;
}

std::ostream &operator<<(std::ostream &o, const Friend &f)
{
    o << f.relation << ", " << f.secret;
    return o;
}

std::ostream &operator<<(std::ostream &o, const Person &p)
{
    o << p.name << ", " << p.age << ", " << address << ", ";
    std::copy(begin(p.neighbors), end(p.neighbors), std::ostream_iterator<Friend>(o, "| "));
    o << ", " << p.secret;    // to do......
    return o;
}
