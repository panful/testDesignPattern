
/**
 * 1. 命令模式
 * 2. 使用命令模式实现撤销
 */

#define TEST2

#ifdef TEST1

#include <format>
#include <iostream>
#include <memory>
#include <string>

/// @brief 命令基类，所有的命令都继承自该类
class Command
{
public:
    virtual void Execute() = 0;

    Command()                   = default;
    virtual ~Command() noexcept = default;

    // void SetExectureArgs(void*, std::any) 通过成员函数设置执行命令的参数
};

/// @brief 不需要参数的简单命令
class Command1 : public Command
{
public:
    void Execute() override
    {
        std::cout << "Execute Command1\n";
    }
};

/// @brief 带参数的复杂命令，参数可以通过构造函数或成员函数设置
class Command2 : public Command
{
public:
    explicit Command2(const std::string& data) : m_data(data)
    {
    }

    void Execute() override
    {
        std::cout << std::format("Execure Command2 : {}\n", m_data);
    }

private:
    std::string m_data {};
};

/// @brief 命令调用者，还可以将命令放入队列中，通过遍历队列执行命令。可以将命令当作一个回调函数，在指定时刻执行该命令
class Invoker
{
public:
    void SetStart(std::unique_ptr<Command> c)
    {
        m_start = std::move(c);
    }

    void SetEnd(std::unique_ptr<Command> c)
    {
        m_end = std::move(c);
    }

    void DoWork()
    {
        std::cout << "Start:\n";
        m_start->Execute();
        std::cout << "End:\n";
        m_end->Execute();
    }

private:
    std::unique_ptr<Command> m_start {};
    std::unique_ptr<Command> m_end {};
};

int main()
{
    auto c1 = std::make_unique<Command1>();
    auto c2 = std::make_unique<Command2>("test data");

    Invoker invoker {};
    invoker.SetStart(std::move(c1));
    invoker.SetEnd(std::move(c2));
    invoker.DoWork();
}

#endif // TEST1

#ifdef TEST2

#include <format>
#include <iostream>
#include <memory>
#include <stack>

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute() = 0;
    virtual void undo()    = 0;
};

/// @brief 对一个int数字自增的命令
class ConcreteCommand : public Command
{
private:
    int& data;    // 操作的数据
    int oldValue; // 用于撤销的旧值

public:
    ConcreteCommand(int& data) : data(data), oldValue(data)
    {
    }

    /// @brief 执行自增操作
    void execute() override
    {
        std::cout << std::format("Increase resulst: {}\n", ++data);
    }

    /// @brief 撤销操作
    void undo() override
    {
        std::cout << std::format("Undo result: {}\n", --data);
    }
};

// 命令调用者
class Invoker
{
private:
    std::stack<std::unique_ptr<Command>> commandHistory;

public:
    void executeCommand(std::unique_ptr<Command> command)
    {
        command->execute();
        commandHistory.push(std::move(command));
    }

    void undoLastCommand()
    {
        if (!commandHistory.empty())
        {
            commandHistory.top()->undo();
            commandHistory.pop();
        }
    }
};

int main()
{
    int originalNumber = 0;
    std::cout << std::format("Original data: {}\n", originalNumber);

    Invoker invoker;
    invoker.executeCommand(std::make_unique<ConcreteCommand>(originalNumber));
    invoker.executeCommand(std::make_unique<ConcreteCommand>(originalNumber));
    invoker.executeCommand(std::make_unique<ConcreteCommand>(originalNumber));
    invoker.executeCommand(std::make_unique<ConcreteCommand>(originalNumber));
    invoker.undoLastCommand();
    invoker.undoLastCommand();

    std::cout << std::format("Final data: {}\n", originalNumber);

    return 0;
}

#endif // TEST2
