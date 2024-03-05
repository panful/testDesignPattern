/**
 * 1. 享元模式
 * 2. 组合模式叶节点使用享元模式
 * 
 */
#define TEST2

#ifdef TEST1

#include <iostream>
#include <string>
#include <unordered_map>

// 抽象享元
class Book
{
public:
    virtual void display(const std::string& location) = 0;
};

// 具体享元
class ConcreteBook : public Book
{
private:
    std::string title;  // 内部状态，可以共享
    std::string author; // 内部状态，可以共享

public:
    /// @brief 享元对象可在不同的情景中使用，必须保证它的状态不被修改，享元对象的参数只能通过构造函数的参数进行一次性初始化，
    ///        它不能对其他对象公开其设置器或共有成员变量
    /// @param title
    /// @param author
    ConcreteBook(const std::string& title, const std::string& author) : title(title), author(author)
    {
    }

    /// @brief 依赖于外部状态，以便在不同情景下使用同一个享元
    /// @param location
    void display(const std::string& location) override
    {
        std::cout << "Book: " << title << " by " << author << ", Located at: " << location << std::endl;
    }
};

// 享元工厂，为了更方便地访问各种享元，可以创建一个工厂方法管理已有享元对象的缓存池
class BookFactory
{
private:
    std::unordered_map<std::string, Book*> bookPool; // 存储共享的书籍对象

public:
    // 获取具体享元对象，如果不存在则创建并加入对象池
    Book* getBook(const std::string& title, const std::string& author)
    {
        std::string key = title + "_" + author;
        if (bookPool.find(key) == bookPool.end())
        {
            bookPool[key] = new ConcreteBook(title, author);
        }
        return bookPool[key];
    }
};

// 图书馆的同一种书（书名和作者相同）可以在不同地方（书架）
int main()
{
    BookFactory bookFactory;

    // 共享对象，内部状态
    Book* book1 = bookFactory.getBook("Design Patterns", "Erich Gamma");
    Book* book2 = bookFactory.getBook("Design Patterns", "Erich Gamma");
    Book* book3 = bookFactory.getBook("Clean Code", "Robert C. Martin");

    // 不同场景下的外部状态
    book1->display("Shelf 1");
    book2->display("Shelf 2");
    book3->display("Shelf 3");

    // 注意：在实际应用中需要释放对象资源，这里为了简化示例未进行释放

    return 0;
}

#endif // TEST1

#ifdef TEST2

#include <iostream>
#include <unordered_map>
#include <vector>

// 抽象组件
class Component
{
public:
    virtual void operation() = 0;
};

// 具体叶子节点
class Leaf : public Component
{
private:
    std::string name;

public:
    Leaf(const std::string& name) : name(name)
    {
    }

    void operation() override
    {
        std::cout << "Leaf: " << name << std::endl;
    }
};

// 具体复合节点
class Composite : public Component
{
private:
    std::string name;
    std::vector<Component*> children; // 存储子节点

public:
    Composite(const std::string& name) : name(name)
    {
    }

    void add(Component* component)
    {
        children.push_back(component);
    }

    void operation() override
    {
        std::cout << "Composite: " << name << std::endl;
        for (Component* child : children)
        {
            child->operation();
        }
    }
};

// 享元工厂
class LeafFactory
{
private:
    std::unordered_map<std::string, Leaf*> leafPool; // 存储共享的叶子节点

public:
    // 获取具体叶子节点，如果不存在则创建并加入对象池
    Leaf* getLeaf(const std::string& name)
    {
        if (leafPool.find(name) == leafPool.end())
        {
            leafPool[name] = new Leaf(name);
        }
        return leafPool[name];
    }
};

int main()
{
    // 创建组合结构
    Composite* root    = new Composite("Root");
    Composite* branch1 = new Composite("Branch 1");
    Composite* branch2 = new Composite("Branch 2");

    LeafFactory leafFactory;

    // 共享叶子节点
    Leaf* leafA = leafFactory.getLeaf("Leaf A");
    Leaf* leafB = leafFactory.getLeaf("Leaf B");
    Leaf* leafC = leafFactory.getLeaf("Leaf C");

    // 组合树
    root->add(branch1);
    root->add(branch2);

    branch1->add(leafA);
    branch1->add(leafB);
    branch2->add(leafA); // 共享叶子节点

    branch2->add(leafC);

    // 执行操作
    root->operation();

    // 注意：在实际应用中需要释放对象资源，这里为了简化示例未进行释放

    return 0;
}

#endif // TEST2
