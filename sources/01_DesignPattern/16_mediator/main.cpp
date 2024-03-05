/**
 * 1. 中介者模式
 * 2. 使用智能指针实现
 */

#define TEST2

#ifdef TEST1

#include <iostream>
#include <string>
/**
 * The Mediator interface declares a method used by components to notify the
 * mediator about various events. The Mediator may react to these events and
 * pass the execution to other components.
 */
class BaseComponent;

class Mediator
{
public:
    virtual void Notify(BaseComponent* sender, std::string event) const = 0;
};

/**
 * The Base Component provides the basic functionality of storing a mediator's
 * instance inside component objects.
 */
class BaseComponent
{
protected:
    Mediator* mediator_;

public:
    BaseComponent(Mediator* mediator = nullptr) : mediator_(mediator)
    {
    }

    void set_mediator(Mediator* mediator)
    {
        this->mediator_ = mediator;
    }
};

/**
 * Concrete Components implement various functionality. They don't depend on
 * other components. They also don't depend on any concrete mediator classes.
 */
class Component1 : public BaseComponent
{
public:
    void DoA()
    {
        std::cout << "Component 1 does A.\n";
        this->mediator_->Notify(this, "A");
    }

    void DoB()
    {
        std::cout << "Component 1 does B.\n";
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent
{
public:
    void DoC()
    {
        std::cout << "Component 2 does C.\n";
        this->mediator_->Notify(this, "C");
    }

    void DoD()
    {
        std::cout << "Component 2 does D.\n";
        this->mediator_->Notify(this, "D");
    }
};

/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */
class ConcreteMediator : public Mediator
{
private:
    Component1* component1_;
    Component2* component2_;

public:
    ConcreteMediator(Component1* c1, Component2* c2) : component1_(c1), component2_(c2)
    {
        this->component1_->set_mediator(this);
        this->component2_->set_mediator(this);
    }

    void Notify(BaseComponent* sender, std::string event) const override
    {
        if (event == "A")
        {
            std::cout << "Mediator reacts on A and triggers following operations:\n";
            this->component2_->DoC();
        }
        if (event == "D")
        {
            std::cout << "Mediator reacts on D and triggers following operations:\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
};

/**
 * The client code.
 */

void ClientCode()
{
    Component1* c1             = new Component1;
    Component2* c2             = new Component2;
    ConcreteMediator* mediator = new ConcreteMediator(c1, c2);
    std::cout << "Client triggers operation A.\n";
    c1->DoA();
    std::cout << "\n";
    std::cout << "Client triggers operation D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}

int main()
{
    ClientCode();
    return 0;
}

#endif // TEST1

#ifdef TEST2

#include <format>
#include <iostream>
#include <list>
#include <memory>

class User;

class Mediator
{
private:
    std::list<std::shared_ptr<User>> m_users {};

public:
    /// @brief 转发消息
    /// @param from
    /// @param message
    void BroadCast(const std::shared_ptr<User>& from, const std::string& message) const;

    /// @brief 注册用户，当中介者收到消息后，会将消息转发给注册的用户
    /// @param user
    void Register(const std::shared_ptr<User>& user)
    {
        m_users.emplace_back(user);
    }
};

class User : public std::enable_shared_from_this<User>
{
private:
    std::weak_ptr<Mediator> m_mediator {};
    std::string m_name {};

public:
    User(const std::string& name, const std::shared_ptr<Mediator>& m) : m_name(name), m_mediator(m)
    {
    }

    /// @brief 用户主动发送消息（发送给中介者）
    /// @param message
    void Send(const std::string& message)
    {
        if (auto ptr = m_mediator.lock())
        {
            ptr->BroadCast(shared_from_this(), message);
        }
    }

    /// @brief 用户被动接收消息（来自中介者）
    /// @param message
    void Recv(const std::string& message)
    {
        std::cout << std::format("\"{}\" receive: \"{}\"\n", m_name, message);
    }
};

void Mediator::BroadCast(const std::shared_ptr<User>& from, const std::string& message) const
{
    for (auto const& user : m_users)
    {
        if (from != user)
        {
            user->Recv(message);
        }
    }
}

// 根据需要可以对 User 和 Mediator 提取虚基类
int main()
{
    auto mediator = std::make_shared<Mediator>();

    auto user1 = std::make_shared<User>("User1", mediator);
    auto user2 = std::make_shared<User>("User2", mediator);
    auto user3 = std::make_shared<User>("User3", mediator);

    // 可以根据情况将注册放在User的构造函数中（注意：此示例不能在构造函数调用 shared_from_this）
    mediator->Register(user1);
    mediator->Register(user2);
    mediator->Register(user3);

    user1->Send("User1's Message: Good luck");
    user2->Send("User2's Message: Hello");
    user3->Send("User3's Message: Great");

    return 0;
}

#endif // TEST2
