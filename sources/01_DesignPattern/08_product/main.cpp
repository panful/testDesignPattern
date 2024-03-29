/**
 * 1. 简单工厂模式
 * 2. 工厂方法模式
 * 3. 抽象工厂模式
 */

#define TEST1

#ifdef TEST1

#include <iostream>
#include <memory>
#include <string>

enum class ProductType
{
    A = 0,
    B,
};

// 抽象产品类
class Product
{
public:
    virtual void operation()    = 0;
    virtual ~Product() noexcept = default;
};

// 具体产品类 A
class ConcreteProductA : public Product
{
public:
    void operation() override
    {
        std::cout << "ConcreteProductA operation." << std::endl;
    }
};

// 具体产品类 B
class ConcreteProductB : public Product
{
public:
    void operation() override
    {
        std::cout << "ConcreteProductB operation." << std::endl;
    }
};

// 简单工厂类
class SimpleFactory
{
public:
    // 创建产品的方法，可以是静态函数，也可以不是
    static std::unique_ptr<Product> createProduct(const ProductType type)
    {
        std::unique_ptr<Product> retval {};
        switch (type)
        {
            case ProductType::A:
                retval = std::make_unique<ConcreteProductA>();
                break;
            case ProductType::B:
                retval = std::make_unique<ConcreteProductB>();
                break;
            default:
                break;
        }
        return retval;
    }
};

int main()
{
    // 使用简单工厂创建具体产品对象
    auto pA = SimpleFactory::createProduct(ProductType::A);
    auto pB = SimpleFactory::createProduct(ProductType::B);

    // 使用产品对象
    pA->operation();
    pB->operation();

    return 0;
}

#endif // TEST1

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

#ifdef TEST3

#include <iostream>
#include <string>

class AbstractProductA
{
public:
    virtual ~AbstractProductA() {};
    virtual std::string UsefulFunctionA() const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ConcreteProductA1 : public AbstractProductA
{
public:
    std::string UsefulFunctionA() const override
    {
        return "The result of the product A1.";
    }
};

class ConcreteProductA2 : public AbstractProductA
{
    std::string UsefulFunctionA() const override
    {
        return "The result of the product A2.";
    }
};

/**
 * Here's the the base interface of another product. All products can interact
 * with each other, but proper interaction is possible only between products of
 * the same concrete variant.
 */
class AbstractProductB
{
    /**
     * Product B is able to do its own thing...
     */
public:
    virtual ~AbstractProductB() {};
    virtual std::string UsefulFunctionB() const = 0;
    /**
     * ...but it also can collaborate with the ProductA.
     *
     * The Abstract Factory makes sure that all products it creates are of the
     * same variant and thus, compatible.
     */
    virtual std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator) const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */
class ConcreteProductB1 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "The result of the product B1.";
    }

    /**
     * The variant, Product B1, is only able to work correctly with the variant,
     * Product A1. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator) const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "The result of the product B2.";
    }

    /**
     * The variant, Product B2, is only able to work correctly with the variant,
     * Product A2. Nevertheless, it accepts any instance of AbstractProductA as an
     * argument.
     */
    std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator) const override
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 */
class AbstractFactory
{
public:
    virtual AbstractProductA* CreateProductA() const = 0;
    virtual AbstractProductB* CreateProductB() const = 0;
};

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
 */
class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA* CreateProductA() const override
    {
        return new ConcreteProductA1();
    }

    AbstractProductB* CreateProductB() const override
    {
        return new ConcreteProductB1();
    }
};

/**
 * Each Concrete Factory has a corresponding product variant.
 */
class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstractProductA* CreateProductA() const override
    {
        return new ConcreteProductA2();
    }

    AbstractProductB* CreateProductB() const override
    {
        return new ConcreteProductB2();
    }
};

/**
 * The client code works with factories and products only through abstract
 * types: AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */

void ClientCode(const AbstractFactory& factory)
{
    const AbstractProductA* product_a = factory.CreateProductA();
    const AbstractProductB* product_b = factory.CreateProductB();
    std::cout << product_b->UsefulFunctionB() << "\n";
    std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

int main()
{
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1* f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactory2* f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    return 0;
}

#endif // TEST3
