
/**
 * 1. 责任链模式
 */

#define TEST1

#ifdef TEST1

#include <iostream>
#include <memory>

class Handler
{
public:
    virtual std::unique_ptr<Handler>& SetNext(std::unique_ptr<Handler>) = 0;
    virtual void Handle(int)                                            = 0;
};

class AbstractHandler : public Handler
{
public:
    std::unique_ptr<Handler>& SetNext(std::unique_ptr<Handler> next) override
    {
        m_next = std::move(next);
        return m_next;
    }

    void Handle(int n = 0) override
    {
        std::cout << "Unknown number\n";
    }

protected:
    std::unique_ptr<Handler> m_next {};
};

class Thousand : public AbstractHandler
{
public:
    void Handle(int n) override
    {
        if (n > 1'000)
        {
            std::cout << "Over a thousand\n";
        }
        else if (m_next)
        {
            m_next->Handle(n);
        }
    }
};

class Hundred : public AbstractHandler
{
public:
    void Handle(int n) override
    {
        if (n > 100)
        {
            std::cout << "Over one hundred\n";
        }
        else if (m_next)
        {
            m_next->Handle(n);
        }
    }
};

class Ten : public AbstractHandler
{
public:
    void Handle(int n) override
    {
        if (n > 10)
        {
            std::cout << "Over one ten\n";
        }
        else if (m_next)
        {
            m_next->Handle(n);
        }
        else
        {
            AbstractHandler::Handle();
        }
    }
};

int main()
{
    auto number = std::make_unique<Thousand>();
    number->SetNext(std::make_unique<Hundred>())->SetNext(std::make_unique<Ten>());
    number->Handle(18);

    // 上面的代码和下面的 if else 一样，但是 if else只能硬编码
    int num { 66 };
    if (num > 1'000)
    {
    }
    else if (num > 100)
    {
    }
    else if (num > 10)
    {
    }
    else
    {
    }
}

#endif // TEST1
