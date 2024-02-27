#include <iostream>

// 子系统类 1
class Subsystem1
{
public:
    void operation1()
    {
        std::cout << "Subsystem1: Operation 1\n";
    }

    void operation2()
    {
        std::cout << "Subsystem1: Operation 2\n";
    }
};

// 子系统类 2
class Subsystem2
{
public:
    void operation1()
    {
        std::cout << "Subsystem2: Operation 1\n";
    }

    void operation2()
    {
        std::cout << "Subsystem2: Operation 2\n";
    }
};

/// @brief 外观类
/// @details 向客户端暴露的所有接口都放在这个类中，可以使用单例
class Facade
{
private:
    Subsystem1 subsystem1;
    Subsystem2 subsystem2;

public:
    void operation1()
    {
        std::cout << "Facade: Operation 1\n";
        subsystem1.operation1();
        subsystem2.operation1();
    }

    void operation2()
    {
        std::cout << "Facade: Operation 2\n";
        subsystem1.operation2();
        subsystem2.operation2();
    }
};

int main()
{
    // 使用外观模式
    Facade facade;
    facade.operation1();
    facade.operation2();

    return 0;
}
