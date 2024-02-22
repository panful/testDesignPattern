
#include <iostream>

class Singleton
{
public:
    static Singleton* GetInstance() noexcept
    {
        std::cout << "Get instance\n";
        // C++11之后 static变量线程安全
        static Singleton instance {};
        return &instance;
    }

public:
    void f1()
    {
        std::cout << __func__ << '\n';
    }

    void f2()
    {
        std::cout << __func__ << '\n';
    }

private:
    Singleton() noexcept
    {
        std::cout << "Construct\n";
    }

    ~Singleton() noexcept
    {
        std::cout << "Destruct\n";
    }
};

int main()
{
    std::cout << "--------------------------------------------------\n";

    if (auto p = Singleton::GetInstance())
    {
        p->f1();
        p->f2();
    }

    Singleton::GetInstance()->f1();
    Singleton::GetInstance()->f2();

    std::cout << "--------------------------------------------------\n";
}
