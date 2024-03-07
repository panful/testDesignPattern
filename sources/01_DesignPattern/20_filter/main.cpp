#include <iostream>
#include <string>
#include <vector>

// 定义被过滤的对象类
class Person
{
public:
    std::string name;
    std::string gender;
    int age;

    Person(const std::string& name, const std::string& gender, int age) : name(name), gender(gender), age(age)
    {
    }
};

// 定义过滤器接口
class Filter
{
public:
    virtual std::vector<Person> filter(const std::vector<Person>& persons) const = 0;
};

// 具体的过滤器实现 - 男性过滤器
class MaleFilter : public Filter
{
public:
    std::vector<Person> filter(const std::vector<Person>& persons) const override
    {
        std::vector<Person> result;
        for (const auto& person : persons)
        {
            if (person.gender == "Male")
            {
                result.push_back(person);
            }
        }
        return result;
    }
};

// 具体的过滤器实现 - 成年人过滤器
class AdultFilter : public Filter
{
public:
    std::vector<Person> filter(const std::vector<Person>& persons) const override
    {
        std::vector<Person> result;
        for (const auto& person : persons)
        {
            if (person.age >= 18)
            {
                result.push_back(person);
            }
        }
        return result;
    }
};

// 定义客户端代码，使用过滤器
void printPersons(const std::vector<Person>& persons)
{
    for (const auto& person : persons)
    {
        std::cout << "Name: " << person.name << ", Gender: " << person.gender << ", Age: " << person.age << std::endl;
    }
}

int main()
{
    // 创建一组人员对象
    std::vector<Person> persons {
        // clang-format off
        { "Alice",   "Female", 25 }, 
        { "Bob",     "Male",   30 }, 
        { "Charlie", "Male",   17 }, 
        { "David",   "Male",   22 },
        { "Emma",    "Female", 19 },
        // clang-format on
    };

    // 创建不同的过滤器
    MaleFilter maleFilter;
    AdultFilter adultFilter;

    // 使用过滤器过滤人员
    std::cout << "Male Persons:" << std::endl;
    auto malePersons = maleFilter.filter(persons);
    printPersons(malePersons);

    std::cout << "\nAdult Persons:" << std::endl;
    auto adultPersons = adultFilter.filter(persons);
    printPersons(adultPersons);

    return 0;
}
