/**
 * 1.
 * 2. 工厂方法模式
 * 
 */

#define TEST2

#ifdef TEST2

#include <iostream>
#include <memory>
#include <string>

class Product
{
public:
    virtual ~Product()
    {
    }

    virtual std::string Operation() const = 0;
};

class ProductMouse : public Product
{
public:
    std::string Operation() const override
    {
        return "Mouse";
    }
};

class ProductKeyboard : public Product
{
public:
    std::string Operation() const override
    {
        return "Keyboard";
    }
};

class Factory
{
public:
    virtual ~Factory() {};
    virtual std::unique_ptr<Product> FactoryMethod() const = 0;

    std::string SomeOperation() const
    {
        auto product = this->FactoryMethod();
        auto result  = "Do something: " + product->Operation();

        return result;
    }
};

class FactoryMouse : public Factory
{
public:
    std::unique_ptr<Product> FactoryMethod() const override
    {
        return std::make_unique<ProductMouse>();
    }
};

class FactoryKeyboard : public Factory
{
public:
    std::unique_ptr<Product> FactoryMethod() const override
    {
        return std::make_unique<ProductKeyboard>();
    }
};

// 如果有新的产品，只需要新建一个产品类，新建一个创建该产品的工厂类，不需要修改原来的代码
int main()
{
    std::unique_ptr<Factory> mouse = std::make_unique<FactoryMouse>();
    std::cout << mouse->SomeOperation() << '\n';

    std::unique_ptr<Factory> keyboard = std::make_unique<FactoryKeyboard>();
    std::cout << keyboard->SomeOperation() << '\n';

    return 0;
}

#endif // TEST2
