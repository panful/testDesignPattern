
/**
 * 1. std::call_once 单例类
 * 2. crtp 单例基类
 * 3. C++11之后静态变量线程安全
 */

#define TEST1

#ifdef TEST1

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Singleton
{
public:
    static Singleton* GetInstance()
    {
        static std::once_flag onceFlag; // 此处onceFlag必须是静态的
        std::call_once(onceFlag,
            []()
            {
                if (m_instance == nullptr)
                {
                    std::cout << "new Singleton\n";
                    m_instance = new Singleton();
                }
            });
        return m_instance;
    }

    static void Destroy()
    {
        static std::once_flag onceFlag;
        std::call_once(onceFlag,
            []()
            {
                if (m_instance)
                {
                    std::cout << "destroy Singleton\n";
                    delete m_instance;
                    m_instance = nullptr;
                }
            });
    }

    void Func()
    {
        static size_t n = 0;
        std::cout << " --- " << n++ << " Test: Func()\n";
    }

private:
    inline static Singleton* m_instance { nullptr }; // c++17

    Singleton()                      = default;
    ~Singleton() noexcept            = default;
    Singleton(const Singleton&)      = delete;
    void operator=(const Singleton&) = delete;
};

int main()
{
    std::cout << "--- start ---\n";

    std::vector<std::thread> threads;

    constexpr size_t numOfThreads { 1000 };
    for (size_t i = 0; i < numOfThreads; i++)
    {
        // new Singleton()只会被调用一次
        std::thread t([]() { Singleton::GetInstance(); });
        threads.emplace_back(std::move(t));
    }

    for (auto&& t : threads)
    {
        t.join();
    }

    std::cout << "--- end ---\n";

    return 0;
}

#endif // TEST1

#ifdef TEST2

#include <iostream>
#include <mutex>

// crtp https://mp.weixin.qq.com/s/giSDMWLO0d7t3fX-ZC7eVg

template <typename T>
class SingletonBase
{
public:
    static T* GetInstance() noexcept
    {
        static std::once_flag flag;
        std::call_once(flag, []() { m_instance = new T(); });
        return m_instance;
    }

    static void Destroy() noexcept
    {
        static std::once_flag flag;
        std::call_once(flag,
            []()
            {
                if (m_instance)
                {
                    delete m_instance;
                    m_instance = nullptr;
                }
            });
    };

private:
    inline static T* m_instance { nullptr };

protected:
    SingletonBase()                                = default;
    virtual ~SingletonBase() noexcept              = default;
    SingletonBase& operator=(const SingletonBase&) = delete;
    SingletonBase(const SingletonBase&)            = delete;

    // 不需要实现移动操作，移动操作只有在用户没有显示声明拷贝操作和析构函数时才会自动生成
    // SingletonBase& operator=(SingletonBase&&) noexcept;
    // SingletonBase(SingletonBase&&) noexcept;
};

class Derived final : public SingletonBase<Derived>
{
    friend class SingletonBase<Derived>;

public:
    void Test()
    {
        std::cout << m_number << '\n';
    }

private:
    int m_number { 666 };

private:
    Derived()                    = default;
    ~Derived() noexcept override = default;

    // 拷贝操作都会被继承，所以此处不声明拷贝操作为delete，也不能使用该类的拷贝操作
};

int main()
{
    Derived::GetInstance()->Test();
    Derived::Destroy();

    return 0;
}

#endif // TEST2

#ifdef TEST3

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

#endif // TEST3
