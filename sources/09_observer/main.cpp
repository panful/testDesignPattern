
#include <iostream>
#include <list>
#include <string>

using namespace std::string_literals;

// 通知的消息类型
enum class NotifyType
{
    Eat = 0,
    Drink,
    Play,
    Work,
};

class Observer;

// 通知者（观察目标）
class Subject
{
protected:
    std::list<Observer*> m_observers;

public:
    void attach(Observer*);    // 注册（添加一个观察者）
    void detach(Observer*);    // 注销（删除一个观察者）
    virtual void notify() = 0; // 通知
};

// 观察者
class Observer
{
public:
    virtual void update(NotifyType type) = 0; // 更新
    virtual ~Observer() {};
};

// 具体的观察者：员工A
class WorkerA : public Observer
{
    void update(NotifyType type) override;
};

// 具体的观察者：员工B
class WorkerB : public Observer
{
    void update(NotifyType type) override;
};

// 具体的观察者：员工C
class WorkerC : public Observer
{
    void update(NotifyType type) override;
};

// 具体的通知者：组长
class Leader : public Subject
{
public:
    void notify() override;
};

// 具体的通知者：经理
class Manager : public Subject
{
public:
    void notify() override;
};

// 具体的通知者：老板
class Boss : public Subject
{
public:
    void notify() override;
};

void Subject::attach(Observer* obs)
{
    m_observers.emplace_back(obs);
}

void Subject::detach(Observer* obs)
{
    auto it = m_observers.begin();
    while (it != m_observers.end())
    {
        if (*it == obs)
            m_observers.erase(it);
        it++;
    }
}

void Leader::notify()
{
    // 组长通知一起去洗脚
    std::cout << "\t组长发通知了\n";
    for (const auto& elem : m_observers)
    {
        elem->update(NotifyType::Play);
    }
}

void Manager::notify()
{
    // 经理通知今晚加班
    std::cout << "\t经理发通知了\n";
    for (const auto& elem : m_observers)
    {
        elem->update(NotifyType::Work);
    }
}

void Boss::notify()
{
    // 老板通知今晚一起吃饭喝酒
    std::cout << "\t老板发通知了\n";
    for (const auto& elem : m_observers)
    {
        elem->update(NotifyType::Eat);
        elem->update(NotifyType::Drink);
    }
}

void WorkerA::update(NotifyType type)
{
    switch (type)
    {
        case NotifyType::Eat:
            std::cout << "WorkerA:\t去吃饭咯。\n";
            break;
        case NotifyType::Drink:
            std::cout << "WorkerA:\t去喝酒咯。\n";
            break;
        case NotifyType::Play:
            std::cout << "WorkerA:\t去洗脚咯。\n";
            break;
        case NotifyType::Work:
            std::cout << "WorkerA:\t装作认真工作的样子。\n";
            break;
        default:
            break;
    }
}

void WorkerB::update(NotifyType type)
{
    switch (type)
    {
        case NotifyType::Eat:
            std::cout << "WorkerB:\t我不去吃饭。\n";
            break;
        case NotifyType::Drink:
            std::cout << "WorkerB:\t我不去喝酒。\n";
            break;
        case NotifyType::Play:
            std::cout << "WorkerB:\t一起去洗脚咯。\n";
            break;
        case NotifyType::Work:
            std::cout << "WorkerB:\t加你麻痹班！\n";
            break;
        default:
            break;
    }
}

void WorkerC::update(NotifyType type)
{
    switch (type)
    {
        case NotifyType::Eat:
            std::cout << "WorkerC:\t我先回家了。\n";
            break;
        case NotifyType::Drink:
            std::cout << "WorkerC:\t我不会喝酒。\n";
            break;
        case NotifyType::Play:
            std::cout << "WorkerC:\t这次去哪洗脚？\n";
            break;
        case NotifyType::Work:
            std::cout << "WorkerC:\t我要带孩子先溜了，你们好好加班。\n";
            break;
        default:
            break;
    }
}

// 一般情况下，观察目标只有一个，即一对多的关系
int main()
{
#ifdef WIN32
    system("chcp 65001"); // 将输出终端的字符集设置为 utf-8
#endif                    // WIN32

    // 观察目标对象
    Subject* leader  = new Leader();
    Subject* manager = new Manager();
    Subject* boss    = new Boss();

    // 观察者对象
    Observer* workerA = new WorkerA();
    Observer* workerB = new WorkerB();
    Observer* workerC = new WorkerC();

    //---------------------------------------------------
    // 添加观察目标的观察者
    leader->attach(workerA);
    leader->attach(workerB);
    leader->attach(workerC);

    manager->attach(workerA);
    manager->attach(workerB);
    manager->attach(workerC);

    boss->attach(workerA);
    boss->attach(workerB);
    boss->attach(workerC);

    //---------------------------------------------------
    // 观察目标状态改变发出通知
    leader->notify();
    manager->notify();
    boss->notify();

    //---------------------------------------------------
    // 移除观察目标的观察者
    leader->detach(workerA);
    leader->detach(workerB);
    leader->detach(workerC);

    manager->detach(workerA);
    manager->detach(workerB);
    manager->detach(workerC);

    boss->detach(workerA);
    boss->detach(workerB);
    boss->detach(workerC);

    return 0;
}
