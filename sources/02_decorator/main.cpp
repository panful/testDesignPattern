/**
 * 1. 装饰模式演示
 * 2. 创建装饰器时，避免多次创建组件的资源
 */

#define TEST2

#ifdef TEST1

#include <format>
#include <iostream>
#include <memory>
#include <string>

// 咖啡基础组件
class Coffee
{
public:
    Coffee()
    {
        std::cout << "Create a coffee\n";
    }

    virtual ~Coffee()
    {
        std::cout << "Destroy a coffee\n";
    }

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
    std::unique_ptr<Coffee> coffee { nullptr };

public:
    CoffeeDecorator(std::unique_ptr<Coffee> c) : coffee(std::move(c))
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
    MilkDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c))
    {
    }

    std::string getDescription() const override
    {
        return coffee->getDescription() + " + Milk";
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
    TeaDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c))
    {
    }

    std::string getDescription() const override
    {
        return coffee->getDescription() + " + Tea";
    }

    double cost() const override
    {
        return coffee->cost() + 2.0; // 茶价格
    }
};

/**
 * 基类是 Coffee，是一个最基础的咖啡类
 * 可以装饰为 MilkCoffee TeaCoffee MilkAndTeaCoffee
 */
int main()
{
    std::unique_ptr<Coffee> coffee     = std::make_unique<Coffee>();
    std::unique_ptr<Coffee> milk       = std::make_unique<MilkDecorator>(std::make_unique<Coffee>());
    std::unique_ptr<Coffee> tea        = std::make_unique<TeaDecorator>(std::make_unique<Coffee>());
    std::unique_ptr<Coffee> milkAndTea = std::make_unique<TeaDecorator>(std::make_unique<MilkDecorator>(std::make_unique<Coffee>()));

    std::cout << std::format("Coffee: {:<15}Description: {:<20}Cost: {:<5}\n", "Simple", coffee->getDescription(), coffee->cost());
    std::cout << std::format("Coffee: {:<15}Description: {:<20}Cost: {:<5}\n", "Milk", milk->getDescription(), milk->cost());
    std::cout << std::format("Coffee: {:<15}Description: {:<20}Cost: {:<5}\n", "Tea", tea->getDescription(), tea->cost());
    std::cout << std::format("Coffee: {:<15}Description: {:<20}Cost: {:<5}\n", "Milk and Tea", milkAndTea->getDescription(), milkAndTea->cost());

    return 0;
}

#endif // TEST1

#ifdef TEST2

#include <format>
#include <iostream>
#include <memory>
#include <string>

// 咖啡基础组件(虚基类)
class Coffee
{
public:
    Coffee()
    {
        // 如果在此处创建资源，具体的装饰器每次构造时都会调用Coffee的构造函数，
        // CoffeeDecorator还需要一个Coffee类型的参数，因此会多次调用Coffee的构造函数
        // 解决方法：将Coffee定义为虚基类，资源放在SimpleCoffee中创建，这样就不会多次创建资源
        std::cout << "Create a coffee\n";
    }

    virtual ~Coffee()
    {
        std::cout << "Destroy a coffee\n";
    }

    virtual std::string getDescription() const = 0;

    virtual double cost() const = 0;
};

class SimpleCoffee : public Coffee
{
public:
    SimpleCoffee()
    {
        // 可以在此处创建资源，子类无论被装饰多少次，都只创建一次资源，即只调用一次SimpleCoffee的构造函数
        // TODO
        std::cout << "Create a SimpleCoffee\n";
    }

    ~SimpleCoffee() override
    {
        std::cout << "Destroy a SimpleCoffee\n";
    }

    std::string getDescription() const override
    {
        return "Coffee";
    }

    double cost() const override
    {
        return 1.;
    }
};

// 咖啡装饰器基类
class CoffeeDecorator : public Coffee
{
protected:
    std::unique_ptr<Coffee> coffee { nullptr };

public:
    CoffeeDecorator(std::unique_ptr<Coffee> c) : coffee(std::move(c))
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

class MilkDecorator : public CoffeeDecorator
{
public:
    MilkDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c))
    {
    }

    std::string getDescription() const override
    {
        return coffee->getDescription() + " + Milk";
    }

    double cost() const override
    {
        return coffee->cost() + 2.;
    }
};

class TeaDecorator : public CoffeeDecorator
{
public:
    TeaDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c))
    {
    }

    std::string getDescription() const override
    {
        return coffee->getDescription() + " + Tea";
    }

    double cost() const override
    {
        return coffee->cost() + 3.;
    }
};

int main()
{
    std::unique_ptr<Coffee> coffee     = std::make_unique<SimpleCoffee>();
    std::unique_ptr<Coffee> milk       = std::make_unique<MilkDecorator>(std::make_unique<SimpleCoffee>());
    std::unique_ptr<Coffee> tea        = std::make_unique<TeaDecorator>(std::make_unique<SimpleCoffee>());
    std::unique_ptr<Coffee> milkAndTea = std::make_unique<MilkDecorator>(std::make_unique<TeaDecorator>(std::make_unique<SimpleCoffee>()));

    std::cout << std::format("Coffee: {:<15}Description: {:<20}Cost: {:<5}\n", "Simple", coffee->getDescription(), coffee->cost());
    std::cout << std::format("Coffee: {:<15}Description: {:<20}Cost: {:<5}\n", "Milk", milk->getDescription(), milk->cost());
    std::cout << std::format("Coffee: {:<15}Description: {:<20}Cost: {:<5}\n", "Tea", tea->getDescription(), tea->cost());
    std::cout << std::format("Coffee: {:<15}Description: {:<20}Cost: {:<5}\n", "Milk and Tea", milkAndTea->getDescription(), milkAndTea->cost());

    return 0;
}

#endif // TEST2
