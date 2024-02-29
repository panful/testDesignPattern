/**
 * 1. 代理模式
 * 2. RPC 使用代理模式
 */


#define TEST2

#ifdef TEST1

#include <iostream>

/**
 * The Subject interface declares common operations for both RealSubject and the
 * Proxy. As long as the client works with RealSubject using this interface,
 * you'll be able to pass it a proxy instead of a real subject.
 */
class Subject
{
public:
    virtual void Request() const = 0;
};

/**
 * The RealSubject contains some core business logic. Usually, RealSubjects are
 * capable of doing some useful work which may also be very slow or sensitive -
 * e.g. correcting input data. A Proxy can solve these issues without any
 * changes to the RealSubject's code.
 */
class RealSubject : public Subject
{
public:
    void Request() const override
    {
        std::cout << "RealSubject: Handling request.\n";
    }
};

/**
 * The Proxy has an interface identical to the RealSubject.
 */
class Proxy : public Subject
{
    /**
     * @var RealSubject
     */
private:
    RealSubject* real_subject_;

    bool CheckAccess() const
    {
        // Some real checks should go here.
        std::cout << "Proxy: Checking access prior to firing a real request.\n";
        return true;
    }

    void LogAccess() const
    {
        std::cout << "Proxy: Logging the time of request.\n";
    }

    /**
     * The Proxy maintains a reference to an object of the RealSubject class. It
     * can be either lazy-loaded or passed to the Proxy by the client.
     */
public:
    Proxy(RealSubject* real_subject) : real_subject_(new RealSubject(*real_subject))
    {
    }

    ~Proxy()
    {
        delete real_subject_;
    }

    /**
     * The most common applications of the Proxy pattern are lazy loading,
     * caching, controlling the access, logging, etc. A Proxy can perform one of
     * these things and then, depending on the result, pass the execution to the
     * same method in a linked RealSubject object.
     */
    void Request() const override
    {
        if (this->CheckAccess())
        {
            this->real_subject_->Request();
            this->LogAccess();
        }
    }
};

/**
 * The client code is supposed to work with all objects (both subjects and
 * proxies) via the Subject interface in order to support both real subjects and
 * proxies. In real life, however, clients mostly work with their real subjects
 * directly. In this case, to implement the pattern more easily, you can extend
 * your proxy from the real subject's class.
 */
void ClientCode(const Subject& subject)
{
    // ...
    subject.Request();
    // ...
}

int main()
{
    std::cout << "Client: Executing the client code with a real subject:\n";
    RealSubject* real_subject = new RealSubject;
    ClientCode(*real_subject);
    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy:\n";
    Proxy* proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
    return 0;
}

#endif // TEST1

#ifdef TEST2

#include <iostream>
#include <string>

// 服务端
class Server
{
public:
    void run()
    {
        while (true)
        {
            auto request = Recv();
            auto result  = handleRPC(request);
            Send(std::to_string(result));
        }
    }

    int add(int a, int b) const
    {
        return a + b;
    }

    void Send(const std::string&)
    {
    }

    std::string Recv()
    {
        return {};
    }

    // 简单的 RPC 调用处理函数
    int handleRPC(const std::string& request)
    {
        if (request == "add")
        {
            return add(3, 4); // 实际应该根据请求调用对应的函数
        }
        return -1; // 未知的请求
    }
};

// 代理类
class Proxy
{
public:
    Proxy(const std::string& host, int port)
    {
        // 建立网络连接 SOCKET HTTPS ...
    }

    ~Proxy()
    {
    }

    void Send(const std::string&)
    {
    }

    std::string Recv()
    {
        return {};
    }

    // 发送 RPC 请求并接收结果
    int callRPC(const std::string& request)
    {
        Send(request);
        auto result = Recv();
        result      = "666";
        return std::stoi(result);
    }
};

int main()
{
    // 创建服务端
    [[maybe_unused]] Server server {};

    // 创建代理，建立网络连接
    Proxy proxy("127.0.0.1", 8080);

    // 客户端通过代理调用 RPC
    int result = proxy.callRPC("add");
    std::cout << "Result from RPC call: " << result << std::endl;

    return 0;
}

#endif // TEST2
