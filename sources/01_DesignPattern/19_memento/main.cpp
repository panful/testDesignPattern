
#define TEST2


#ifdef TEST2

#include <chrono>
#include <iostream>
#include <memory>
#include <stack>
#include <string>

class Memento
{
public:
    Memento(const std::string& state) : m_someStates(state)
    {
    }

    std::string GetState() const noexcept
    {
        return m_someStates;
    }

private:
    std::string m_someStates {};
};

/// @brief 发起人
class Originator
{
public:
    /// @brief 做一些操作（修改状态）
    void DoSomeThing()
    {
        m_state = std::format("{:%T}", std::chrono::system_clock::now());
    }

    /// @brief 打印状态（调试使用）
    void PrintState() const noexcept
    {
        std::cout << m_state << '\n';
    }

    /// @brief 将当前状态保存到备忘录中
    /// @return
    std::unique_ptr<Memento> Save() const noexcept
    {
        return std::make_unique<Memento>(m_state);
    }

    /// @brief 将状态恢复为所给备忘录中的状态
    /// @param memento
    void Restore(std::unique_ptr<Memento> memento)
    {
        m_state = memento->GetState();
    }

private:
    std::string m_state { "Init state" };
};

/// @brief 负责人
class Caretaker
{
public:
    Caretaker(const std::shared_ptr<Originator>& originator) : m_originator(originator)
    {
    }

    /// @brief 备份状态
    void Backup()
    {
        m_mementos.emplace(m_originator->Save());
    }

    /// @brief 撤销上一次的操作
    void Undo()
    {
        if (m_mementos.empty())
        {
            std::cerr << "History is empty\n";
            return;
        }

        m_originator->Restore(std::move(m_mementos.top()));
        m_mementos.pop();
    }

private:
    std::stack<std::unique_ptr<Memento>> m_mementos {};
    std::shared_ptr<Originator> m_originator {};
};

int main()
{
    auto originator = std::make_shared<Originator>();
    auto caretaker  = std::make_unique<Caretaker>(originator);

    caretaker->Backup();
    originator->DoSomeThing();
    caretaker->Backup();
    originator->DoSomeThing();
    caretaker->Backup();
    originator->DoSomeThing();

    originator->PrintState();
    caretaker->Undo();
    originator->PrintState();
    caretaker->Undo();
    originator->PrintState();
    caretaker->Undo();
    originator->PrintState();
    caretaker->Undo();
}

#endif // TEST2
