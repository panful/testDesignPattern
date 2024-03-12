/**
 * 1. 原型模式
 * 2. 使用智能指针实现原型模式
 */

#define TEST2

#ifdef TEST1

#include <iostream>
#include <string>

// 原型接口类
class Prototype
{
public:
    virtual Prototype* clone() const = 0;
    virtual void display() const     = 0;

    virtual ~Prototype() noexcept = default;
};

// 具体原型类
class ConcretePrototype : public Prototype
{
private:
    std::string data;

public:
    ConcretePrototype(const std::string& data) : data(data)
    {
    }

    // 实现克隆接口
    ConcretePrototype* clone() const override
    {
        return new ConcretePrototype(*this);
    }

    // 实现显示接口
    void display() const override
    {
        std::cout << "Data: " << data << std::endl;
    }
};

int main()
{
    // 创建原型对象
    ConcretePrototype original("Original Data");

    // 使用原型对象创建克隆对象
    ConcretePrototype* cloned = original.clone();

    // 显示原型对象和克隆对象的数据
    std::cout << "Original Object:" << std::endl;
    original.display();

    std::cout << "\nCloned Object:" << std::endl;
    cloned->display();

    // 释放克隆对象的内存
    delete cloned;

    return 0;
}

#endif // TSET1

#ifdef TEST2

#include <iostream>
#include <memory>

class Prototype
{
public:
    virtual ~Prototype() noexcept = default;

    virtual std::unique_ptr<Prototype> Clone() = 0;
};

class ConcretePrototype : public Prototype
{
public:
    std::unique_ptr<Prototype> Clone() override
    {
        // 如果有必要需要实现该类的拷贝构造函数（深拷贝）
        return std::make_unique<ConcretePrototype>(*this);
    }

    ~ConcretePrototype() override
    {
        std::cout << "Destruct\n";
    }
};

int main()
{
    auto c1 = std::make_unique<ConcretePrototype>();
    auto c2 = c1->Clone();
}

#endif // TEST2
