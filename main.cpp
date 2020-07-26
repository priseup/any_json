#include "any.h"
#include "types.h"

void test()
{
    std::string info = "{\"id\":\"1111111\",\"cards\":[0,1,2,3,4,5,6,7,8,9],\"jiaoDiZhu\":\"\"}";

    rapidjson::Document doc;
    doc.Parse<0>(info.c_str());

    rapidjson::Value &dataArray = doc["cards"];

    if (dataArray.IsArray())
    {
        for (rapidjson::SizeType i = 0; i < dataArray.Size(); i++)
        {
            const rapidjson::Value& object = dataArray[i];

            printf("%d\n",object.GetInt());
        }
    }
}

int main() {
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
}

