
#include <iostream>
#include <memory>

class AbstractClass
{
public:
    /// @brief 定义算法的框架
    void TemplateMethod() const
    {
        this->BaseOperation1();
        this->RequiredOperations1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperation2();
        this->BaseOperation3();
        this->Hook2();
    }

protected:
    /// @brief 这些接口在基类中已经定义了默认实现
    void BaseOperation1() const
    {
        std::cout << "Default Base Operation1\n";
    }

    void BaseOperation2() const
    {
        std::cout << "Default Base Operation2\n";
    }

    void BaseOperation3() const
    {
        std::cout << "Default Base Operation3\n";
    }

    /// @brief 子类必须实现的接口
    virtual void RequiredOperations1() const = 0;
    virtual void RequiredOperation2() const  = 0;

    /// @brief 钩子步骤，通常放在算法的重要步骤前后，为子类提供额外的算法扩展点
    virtual void Hook1() const
    {
    }

    virtual void Hook2() const
    {
    }
};

/// @brief 子类必须实现纯虚函数，根据需要决定是否实现其他步骤以及钩子步骤
class ConcreteClass1 : public AbstractClass
{
protected:
    void RequiredOperations1() const override
    {
        std::cout << "ConcreteClass1 Required Operations1\n";
    }

    void RequiredOperation2() const override
    {
        std::cout << "ConcreteClass1 Required Operations2\n";
    }
};

class ConcreteClass2 : public AbstractClass
{
protected:
    void RequiredOperations1() const override
    {
        std::cout << "ConcreteClass2 Required Operations1\n";
    }

    void RequiredOperation2() const override
    {
        std::cout << "ConcreteClass2 Required Operations2\n";
    }

    void Hook1() const override
    {
        std::cout << "This is Hook\n";
    }
};

/// @brief 客户端调用模板方法来执行算法，不必知道具体的类，只需要通过基类对象的接口来工作
/// @param class_
void ClientCode(std::unique_ptr<AbstractClass> class_)
{
    class_->TemplateMethod();
}

int main()
{
    std::unique_ptr<AbstractClass> algorithm1 = std::make_unique<ConcreteClass1>();
    std::unique_ptr<AbstractClass> algorithm2 = std::make_unique<ConcreteClass2>();

    std::cout << "----------------------------------------\n";
    ClientCode(std::move(algorithm1));
    std::cout << "----------------------------------------\n";
    ClientCode(std::move(algorithm2));
    std::cout << "----------------------------------------\n";

    return 0;
}
