/**
 * 1. 装饰模式演示
 * 2. is-a has-a
 */

#define TEST2

#ifdef TEST1

#include <iostream>
#include <string>

// 咖啡基础组件
class Coffee
{
public:
    virtual std::string getDescription() const
    {
        return "Coffee";
    }

    virtual double cost() const
    {
        return 3.0; // 基础咖啡价格
    }
};

// 咖啡装饰器基类
class CoffeeDecorator : public Coffee
{
protected:
    Coffee* coffee;

public:
    CoffeeDecorator(Coffee* c) : coffee(c)
    {
    }

    std::string getDescription() const override
    {
        return coffee->getDescription();
    }

    double cost() const override
    {
        return coffee->cost();
    }
};

// 牛奶装饰器
class MilkDecorator : public CoffeeDecorator
{
public:
    MilkDecorator(Coffee* c) : CoffeeDecorator(c)
    {
    }

    std::string getDescription() const override
    {
        return coffee->getDescription() + ", Milk";
    }

    double cost() const override
    {
        return coffee->cost() + 1.0; // 牛奶价格
    }
};

// 茶装饰器
class TeaDecorator : public CoffeeDecorator
{
public:
    TeaDecorator(Coffee* c) : CoffeeDecorator(c)
    {
    }

    std::string getDescription() const override
    {
        return coffee->getDescription() + ", Tea";
    }

    double cost() const override
    {
        return coffee->cost() + 2.0; // 茶价格
    }
};

int main()
{
    Coffee* coffee               = new Coffee();
    Coffee* coffeeWithMilk       = new MilkDecorator(new Coffee());
    Coffee* coffeeWithTeaAndMilk = new TeaDecorator(new MilkDecorator(new Coffee()));

    std::cout << "Simple Coffee: " << coffee->getDescription() << ", Cost: $" << coffee->cost() << std::endl;
    std::cout << "Coffee with Milk: " << coffeeWithMilk->getDescription() << ", Cost: $" << coffeeWithMilk->cost() << std::endl;
    std::cout << "Coffee with Tea and Milk: " << coffeeWithTeaAndMilk->getDescription() << ", Cost: $" << coffeeWithTeaAndMilk->cost() << std::endl;

    delete coffee;
    delete coffeeWithMilk;
    delete coffeeWithTeaAndMilk;

    return 0;
}

#endif // TEST1

#ifdef TEST2

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#define Log() std::cout << __LINE__ << "\t" << __FUNCTION__ << std::endl;
#define LogStr(str) std::cout << __LINE__ << "\t" << str << std::endl;

class Helper
{
public:
    Helper()
    {
        Log();
    }

    ~Helper()
    {
        Log();
    }

    Helper(const Helper&)            = default;
    Helper(Helper&&)                 = default;
    Helper& operator=(const Helper&) = default;
    Helper& operator=(Helper&&)      = default;
};

class Base
{
protected:
    std::shared_ptr<Helper> m_helper { nullptr };

public:
    Base()
    {
        LogStr("Base");
    }

    explicit Base(int)
    {
        LogStr("Base(int)");
        m_helper = std::make_shared<Helper>();
    }

    Base(const Base& b)
    {
        LogStr("Base(const Base&)");
    }

    Base(Base&& b) noexcept
    {
        LogStr("Base(Base&&)");
    }

    Base& operator=(const Base&)
    {
        LogStr("=Base(const Base&)");
    }

    Base& operator=(Base&&) noexcept
    {
        LogStr("=Base(Base&&)");
    }

    virtual ~Base()
    {
        Log();
    }
};

class Derived : public Base
{
public:
    /// @brief 使用引用传参，这样构造Derived时，就只需要构造一次Base
    /// @param b
    Derived(Base& b) : Base(b), m_base(b)
    {
        Log();
    }

protected:
    Base m_base;
};

int main()
{
    std::map<int, std::shared_ptr<Base>> map;
    {
        Base b(1); // 构造Base 构造Helper
        std::cout << "1-------------\n";
        auto d = std::make_shared<Derived>(b); // 构造Derived，此处调用Base的拷贝构造(2次)，不调用 Base(int)
        std::cout << "2-------------\n";
        auto d2 = d; // 不调用构造、拷贝构造、赋值等，因为是智能指针，只需要增加引用计数
        std::cout << "3-------------\n";
        map[0] = d; // 不调用构造、拷贝构造、赋值等，因为是智能指针，只需要增加引用计数
        std::cout << "4-------------\n";
    }
    std::cout << "5-------------\n";
}

#endif // TEST2