/**
 * 1. 访问者模式
 * 2. 访问者使用模板函数
 */

#define TEST2

#ifdef TEST1

#include <iostream>
#include <vector>

// Forward declaration of Node classes
class CircleNode;
class SquareNode;

// Visitor interface
class Visitor
{
public:
    // 对每种类型的被访问者都需要定义一个对应参数类型的函数
    // 也可以只定义一个参数为 Node 的基函数 void apply(Node&) 但是这样就需要在函数内部判断被访问的类型，一般不这样做
    virtual void apply(CircleNode& circle) = 0;
    virtual void apply(SquareNode& square) = 0;
};

// Node interface
class Node
{
public:
    /// @brief 每个子类都必须重写该方法，所以定义为纯虚函数。节点需要后期（动态）绑定到访问者上，这样才能知道结点的类型
    virtual void accept(Visitor& visitor) = 0;
};

// Concrete CircleNode class
class CircleNode : public Node
{
public:
    CircleNode(double radius) : radius(radius)
    {
    }

    double getRadius() const
    {
        return radius;
    }

    void accept(Visitor& visitor) override
    {
        visitor.apply(*this);
    }

private:
    double radius;
};

// Concrete SquareNode class
class SquareNode : public Node
{
public:
    SquareNode(double side) : side(side)
    {
    }

    double getSide() const
    {
        return side;
    }

    void accept(Visitor& visitor) override
    {
        visitor.apply(*this);
    }

private:
    double side;
};

// Concrete AreaVisitor class
class AreaVisitor : public Visitor
{
public:
    void apply(CircleNode& circle) override
    {
        double area = 3.14159 * circle.getRadius() * circle.getRadius();
        std::cout << "Circle area: " << area << std::endl;
    }

    void apply(SquareNode& square) override
    {
        double area = square.getSide() * square.getSide();
        std::cout << "Square area: " << area << std::endl;
    }
};

// 添加一个新类时，只需要在这个新的类中添加一个accept(Visitor)函数，具体的操作都在访问者(Visitor)中实现
// 需要增加新的功能时，只需要添加一个新的访问者，并在这个访问者中实现具体的操作，最后调用accept函数即可
int main()
{
    // Create some nodes
    CircleNode circle(5.0);
    SquareNode square(4.0);

    // Create a visitor
    AreaVisitor areaVisitor;

    // Accept the visitor on nodes
    circle.accept(areaVisitor);
    square.accept(areaVisitor);

    return 0;
}

#endif // TEST1

#ifdef TEST2

#include <iostream>
#include <memory>
#include <numbers>

class Visitor
{
public:
    template <typename T>
    void Apply(const T&);
};

class Node
{
public:
    virtual ~Node() noexcept = default;

    virtual void Accept(std::unique_ptr<Visitor> visitor) = 0;
};

class Circle : public Node
{
public:
    constexpr double GetRadius() const noexcept
    {
        return 3.;
    }

    void Accept(std::unique_ptr<Visitor> visitor);
};

class Square : public Node
{
public:
    constexpr double GetSide() const noexcept
    {
        return 5.;
    }

    void Accept(std::unique_ptr<Visitor> visitor) override;
};

// 可以不实现这个函数，如果调用到它，编译期就会报错
template <typename T>
void Visitor::Apply(const T&)
{
    std::cout << "Error\n";
}

template <>
void Visitor::Apply(const Circle& c)
{
    std::cout << "Circle Area: " << std::numbers::pi * c.GetRadius() * c.GetRadius() << '\n';
}

template <>
void Visitor::Apply(const Square& s)
{
    std::cout << "Square Area: " << s.GetSide() * s.GetSide() << '\n';
}

// Visitor::Apply 的定义必须在使用Aplly函数之前
void Circle::Accept(std::unique_ptr<Visitor> visitor)
{
    visitor->Apply(*this);
}

void Square::Accept(std::unique_ptr<Visitor> visitor)
{
    visitor->Apply(*this);
}

int main()
{
    Circle c {};
    c.Accept(std::make_unique<Visitor>());

    Square s {};
    s.Accept(std::make_unique<Visitor>());
}

#endif // TEST2
