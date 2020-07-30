#include "any.h"
// #include "types.h"

void test_any()
{
    int i = 0;
    Any a{5};
    Any g{i};
    Any f{std::move(i)};
    Any b(std::string{"345"});
    const Any &c = a;
    std::cout << a.cast<int>() << std::endl;
    std::cout << c.cast<int>() << std::endl;

    Any d{a};
    Any e{std::move(a)};
    printf("d=f\n");
    d = f;

    printf("d=c\n");
    d = c;

    printf("d=move(f)\n");
    d = std::move(f);

    printf("d=5.6\n");
    d = 5.6;

    const std::string &dd = std::string{"string"};
    printf("d=dd\n");
    d = dd;

    std::cout << b.cast<std::string>() << std::endl;

    Any v = std::vector<int>{1, 2, 3, 4};
    std::cout << v.cast<std::vector<int>>().size() << std::endl;
}

int main() {
    /*
    Friend f1{"my best friend", Singer{"rocker", 18}};
    Friend f2{"new friend", "little girl"};

    Person p2{"p2", 3, Address{"china", "shanghai", "putuo"}};
    Address addr1{"china", "beijing", "wangjing", {p2}};

    Person p1{"p1", 4, addr1, {f1, f2}, "the kind!"};

    // TODO. 以下是示例代码，需要笔试者具体实现
    auto json = dump(p1)             // 序列化
    std::cout << json << std::endl   // 打印序列化结果
    std::cout << p1 << std::endl     // 打印 Person 对象
    auto pp = parse(json);           // 反序列化
    assert(p1 == pp)                 // 反序列化的结果是对的
    */

}

