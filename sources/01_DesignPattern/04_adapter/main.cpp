/**
 * 1. 适配器模式
 * 2. 多重继承实现适配器模式
 * 3.
 */

#define TEST3

#ifdef TEST1

#include <format>
#include <iostream>
#include <memory>
#include <string>

/// @brief 适配器基类
class Target
{
public:
    virtual ~Target() = default;

    /// @brief 经过适配器转换后，使用统一的接口输出统一的类型
    /// @return
    virtual std::string Request() const = 0;
};

/// @brief 被适配者
class Adaptee
{
public:
    /// @brief 获取被适配者的数据
    /// @return
    std::string SpecificRequest() const
    {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/// @brief 适配器
class Adapter : public Target
{
private:
    std::unique_ptr<Adaptee> adaptee_;

public:
    /// @brief 将被适配者当作参数传给适配器
    /// @param adaptee
    Adapter(std::unique_ptr<Adaptee> adaptee) : adaptee_(std::move(adaptee))
    {
    }

    /// @brief 生成适配后的结果
    /// @return
    std::string Request() const override
    {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "TRANSLATED => " + to_reverse;
    }
};

int main()
{
    auto adaptee = std::make_unique<Adaptee>();                   // 被适配者
    auto adapter = std::make_unique<Adapter>(std::move(adaptee)); // 适配器

    std::cout << std::format("Input: {}\nOutput: {}\n", adaptee->SpecificRequest(), adapter->Request());

    return 0;
}

#endif // TEST1

#ifdef TEST2

#include <format>
#include <iostream>
#include <memory>
#include <string>

/// @brief 适配器基类
class Target
{
public:
    virtual ~Target() = default;

    /// @brief 经过适配器转换后，使用统一的接口输出统一的类型
    /// @return
    virtual std::string Request() const = 0;
};

/// @brief 被适配者
class Adaptee
{
public:
    std::string SpecificRequest() const
    {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/// @brief 通过多重继承，实现适配器，这样就不用将被适配者当作参数传入适配器
class Adapter : public Target,
                public Adaptee
{
public:
    /// @brief 生成适配后的结果
    /// @return
    std::string Request() const override
    {
        std::string to_reverse = this->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "TRANSLATED => " + to_reverse;
    }
};

int main()
{
    auto adapter = std::make_unique<Adapter>(); // 适配器

    std::cout << std::format("Input: {}\nOutput: {}\n", adapter->SpecificRequest(), adapter->Request());

    return 0;
}

#endif // TEST2

#ifdef TEST3

#include <format>
#include <iostream>
#include <memory>
#include <string>

/// @brief 适配器基类
class Target
{
public:
    virtual ~Target() = default;

    /// @brief 经过适配器转换后，使用统一的接口输出统一的类型
    /// @return
    virtual std::string Request() const = 0;
};

/// @brief 被适配者（委托类）
class Adaptee
{
public:
    /// @brief 将输入转换为指定输出
    /// @return
    std::string SpecificRequest(/*some args*/) const
    {
        std::string to_reverse { ".eetpadA eht fo roivaheb laicepS" };
        std::reverse(to_reverse.begin(), to_reverse.end());
        return to_reverse;
    }

    /// @brief 根据需要设置数据转换的一些参数
    void SetAttributes()
    {
    }
};

/// @brief 适配器
class Adapter : public Target
{
private:
    std::unique_ptr<Adaptee> adaptee_;

public:
    /// @brief 将被适配者当作参数传给适配器
    /// @param adaptee
    Adapter(std::unique_ptr<Adaptee> adaptee) : adaptee_(std::move(adaptee))
    {
    }

    /// @brief 调用委托类，将输入转换为指定内容后输出
    /// @return
    std::string Request() const override
    {
        return "TRANSLATED => " + this->adaptee_->SpecificRequest();
    }
};

int main()
{
    auto adaptee = std::make_unique<Adaptee>();                   // 被适配者
    auto adapter = std::make_unique<Adapter>(std::move(adaptee)); // 适配器

    std::cout << std::format("Input: {}\nOutput: {}\n", adaptee->SpecificRequest(), adapter->Request());

    return 0;
}

#endif // TEST3
