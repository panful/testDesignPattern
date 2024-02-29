#include <format>
#include <iostream>

class State;

class Context
{
private:
    State* currentState;

public:
    Context(State* state);

    void setState(State* state);

    void open();
    void close();
    void run();
    void stop();
};

// State 接口
class State
{
public:
    virtual void open()  = 0;
    virtual void close() = 0;
    virtual void run()   = 0;
    virtual void stop()  = 0;

    void SetContext(Context* c)
    {
        this->context = c;
    }

protected:
    Context* context;
};

// 具体状态类 - 开门状态
class OpenState : public State
{
public:
    void open() override
    {
        std::cout << std::format("State: {:<10} Operation: {:<10} Resulst: {}\n", "Open", "Open", "The door is already open.");

        context->setState(this);
        this->SetContext(context);
    }

    void close() override;

    void run() override
    {
        std::cout << std::format("State: {:<10} Operation: {:<10} Resulst: {}\n", "Open", "Run", "Please turn off the elevator before running it.");
    }

    void stop() override
    {
        std::cout << std::format("State: {:<10} Operation: {:<10} Resulst: {}\n", "Open", "Stop", "Stopping the elevator.");
    }
};

// 具体状态类 - 关门状态
class CloseState : public State
{
public:
    void open() override
    {
        std::cout << std::format("State: {:<10} Operation: {:<10} Resulst: {}\n", "Close", "Open", "Opening the door.");

        auto open = new OpenState();
        context->setState(open);
        open->SetContext(context);
    }

    void close() override
    {
        std::cout << std::format("State: {:<10} Operation: {:<10} Resulst: {}\n", "Close", "Close", "The door is already closed.");

        context->setState(this);
        this->SetContext(context);
    }

    void run() override
    {
        std::cout << std::format("State: {:<10} Operation: {:<10} Resulst: {}\n", "Close", "Run", "The elevator is running.");
    }

    void stop() override
    {
        std::cout << std::format("State: {:<10} Operation: {:<10} Resulst: {}\n", "Close", "Stop", "Stopping the elevator.");
    }
};

void OpenState::close()
{
    std::cout << std::format("State: {:<10} Operation: {:<10} Resulst: {}\n", "Open", "Close", "Closing the door.");

    auto close = new CloseState();
    context->setState(close);
    close->SetContext(context);
}

Context::Context(State* state) : currentState(state)
{
}

void Context::setState(State* state)
{
    currentState = state;
}

void Context::open()
{
    currentState->open();
}

void Context::close()
{
    currentState->close();
}

void Context::run()
{
    currentState->run();
}

void Context::stop()
{
    currentState->stop();
}

/**
 * 电梯共有四种状态：打开、关闭、运行、停止
 * 当处于打开状态时，不能再打开，可以关闭
 * 当处于关闭状态时，不能再关闭，可以打开
 * 注意：程序没有考虑内存泄漏
 */

int main()
{
    // 初始状态为关门
    auto state   = new CloseState();
    auto context = new Context(state);
    state->SetContext(context);

    context->open(); // Opening the door
    context->run();  // The elevator is running
    context->stop(); // Stopping the elevator

    context->close(); // Closing the door
    context->open();  // Opening the door
    context->open();  // The door is already open

    return 0;
}
