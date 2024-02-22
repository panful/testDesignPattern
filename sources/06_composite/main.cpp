/**
 * 1. 组合模式
 * 2. 
 */


#define TEST1

#ifdef TEST1

#include <algorithm>
#include <iostream>
#include <list>
#include <string>

class Component
{
protected:
    Component* parent_;

public:
    virtual ~Component()
    {
    }

    /// @brief 可选的，设置和获取组件的父级
    /// @param parent
    void SetParent(Component* parent)
    {
        this->parent_ = parent;
    }

    Component* GetParent() const
    {
        return this->parent_;
    }

    virtual void Add(Component* component)
    {
    }

    virtual void Remove(Component* component)
    {
    }

    /// @brief 组件是否可以承载子级
    /// @return
    virtual bool IsComposite() const
    {
        return false;
    }

    virtual std::string Operation() const = 0;
};

/// @brief 叶节点
class Leaf : public Component
{
public:
    std::string Operation() const override
    {
        return "Leaf";
    }
};

/// @brief 组节点
class Composite : public Component
{
protected:
    std::list<Component*> children_;

public:
    void Add(Component* component) override
    {
        this->children_.push_back(component);
        component->SetParent(this);
    }

    void Remove(Component* component) override
    {
        children_.remove(component);
        component->SetParent(nullptr);
    }

    bool IsComposite() const override
    {
        return true;
    }

    std::string Operation() const override
    {
        // 递归遍历所有叶节点
        std::string result;
        for (const Component* c : children_)
        {
            if (c == children_.back())
            {
                result += c->Operation();
            }
            else
            {
                result += c->Operation() + " + ";
            }
        }
        return "Branch(" + result + ")";
    }
};

int main()
{
    Component* simple = new Leaf;
    std::cout << "Simple component:\n";
    std::cout << simple->Operation() << "\n\n";

    //---------------------------------------------------------------
    Component* leaf_1  = new Leaf;
    Component* leaf_2  = new Leaf;
    Component* branch1 = new Composite;
    branch1->Add(leaf_1);
    branch1->Add(leaf_2);

    Component* leaf_3  = new Leaf;
    Component* branch2 = new Composite;
    branch2->Add(leaf_3);

    Component* tree = new Composite;
    tree->Add(branch1);
    tree->Add(branch2);

    std::cout << "Composite tree:\n";
    std::cout << tree->Operation() << "\n\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;

    return 0;
}

#endif // TEST1
