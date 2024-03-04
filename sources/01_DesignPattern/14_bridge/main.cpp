#include <iostream>

// 实现部分的接口 - 颜色
class Color
{
public:
    virtual void applyColor() = 0;
};

// 具体实现部分 - 红色
class RedColor : public Color
{
public:
    void applyColor() override
    {
        std::cout << "Applying Red Color" << std::endl;
    }
};

// 具体实现部分 - 绿色
class GreenColor : public Color
{
public:
    void applyColor() override
    {
        std::cout << "Applying Green Color" << std::endl;
    }
};

// 抽象部分的接口 - 图形
class Shape
{
protected:
    Color* color;

public:
    Shape(Color* col) : color(col)
    {
    }

    virtual void draw() = 0;
};

// 具体抽象部分 - 三角形
class Triangle : public Shape
{
public:
    Triangle(Color* col) : Shape(col)
    {
    }

    void draw() override
    {
        std::cout << "Drawing Triangle ";
        color->applyColor();
    }
};

// 具体抽象部分 - 圆形
class Circle : public Shape
{
public:
    Circle(Color* col) : Shape(col)
    {
    }

    void draw() override
    {
        std::cout << "Drawing Circle ";
        color->applyColor();
    }
};

int main()
{
    // 创建具体实现部分 - 颜色
    Color* red   = new RedColor();
    Color* green = new GreenColor();

    // 创建具体抽象部分 - 图形，并与颜色组合
    Shape* redTriangle = new Triangle(red);
    Shape* greenCircle = new Circle(green);

    // 绘制图形
    redTriangle->draw();
    greenCircle->draw();

    delete red;
    delete green;
    delete redTriangle;
    delete greenCircle;

    return 0;
}
