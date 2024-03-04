#include <iostream>
#include <string>

// 产品类
class Product
{
public:
    void setPartA(const std::string& partA)
    {
        partA_ = partA;
    }

    void setPartB(const std::string& partB)
    {
        partB_ = partB;
    }

    void setPartC(const std::string& partC)
    {
        partC_ = partC;
    }

    void show() const
    {
        std::cout << "Product Parts: " << partA_ << ", " << partB_ << ", " << partC_ << std::endl;
    }

private:
    std::string partA_;
    std::string partB_;
    std::string partC_;
};

// 抽象生成器类
class Builder
{
public:
    virtual void buildPartA()   = 0;
    virtual void buildPartB()   = 0;
    virtual void buildPartC()   = 0;
    virtual Product getResult() = 0;
};

// 具体生成器类，可以根据需要定义多个生成器类
class ConcreteBuilder : public Builder
{
public:
    void buildPartA() override
    {
        product_.setPartA("PartA");
    }

    void buildPartB() override
    {
        product_.setPartB("PartB");
    }

    void buildPartC() override
    {
        product_.setPartC("PartC");
    }

    Product getResult() override
    {
        return product_;
    }

private:
    Product product_;
};

// 指导者类
class Director
{
public:
    void construct(Builder& builder)
    {
        builder.buildPartA();
        builder.buildPartB();
        builder.buildPartC();
    }
};

int main()
{
    ConcreteBuilder builder;
    Director director;

    director.construct(builder);

    Product product = builder.getResult();
    product.show();

    return 0;
}
