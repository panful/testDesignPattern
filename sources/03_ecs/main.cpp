#include <iostream>
#include <unordered_map>
#include <vector>

/// @brief 实体
struct Entity
{
    int id;

    bool operator==(Entity const& e) const noexcept
    {
        return e.id == this->id;
    }
};

namespace std {
template <>
struct hash<Entity>
{
    using argument_type = Entity;
    using result_type   = size_t;

    result_type operator()(argument_type const& e) const
    {
        return e.id;
    }
};

} // namespace std

/// @brief 位置组件
struct PositionComponent
{
    float x, y;
};

/// @brief 速度组件
struct VelocityComponent
{
    float x, y;
};

/// @brief 系统基类
class System
{
public:
    virtual void Update() = 0;
};

class MoveSystem : public System
{
public:
    MoveSystem(Entity e) : entity_(e)
    {
    }

    void Update() override
    {
        // TODO
        // auto dt      = 1.f;
        // auto pos     = ECS.GetPosition();
        // auto vel     = ECS.GetVelocity();
        // auto nextPos = pos + vel * dt;
        // ECS.SetPosition(entity_, nextPos);

        static int test { 0 };
        std::cout << test++ << '\n';
    }

private:
    Entity entity_;
};

/// @brief ECS管理器 EntityManager
class ECS
{
public:
    Entity CreateEntity()
    {
        Entity entity { nextEntityId_++ };
        entities_.push_back(entity);
        return entity;
    }

    void AddComponent(Entity entity, PositionComponent position)
    {
        positions_[entity] = position;
    }

    void AddComponent(Entity entity, VelocityComponent velocity)
    {
        velocities_[entity] = velocity;
    }

    void AddSystem(System* system)
    {
        systems_.emplace_back(system);
    };

    PositionComponent GetPosition(Entity e) const
    {
        return positions_.at(e);
    }

    VelocityComponent GetVelocity(Entity e) const
    {
        return velocities_.at(e);
    }

    void SetPosition(Entity e, PositionComponent pos)
    {
        positions_[e] = pos;
    }

    void SetVelocity(Entity e, VelocityComponent vel)
    {
        velocities_[e] = vel;
    }

    void Update()
    {
        for (auto& system : systems_)
        {
            system->Update();
        }
    }

private:
    std::vector<Entity> entities_;
    std::unordered_map<Entity, PositionComponent> positions_;
    std::unordered_map<Entity, VelocityComponent> velocities_;
    std::vector<System*> systems_;
    int nextEntityId_ = 1;
};

int main()
{
    ECS ecs;

    Entity entity1 = ecs.CreateEntity();
    ecs.AddComponent(entity1, PositionComponent { 0.0f, 0.0f });
    ecs.AddComponent(entity1, VelocityComponent { 0.0f, 2.0f });

    Entity entity2 = ecs.CreateEntity();
    ecs.AddComponent(entity2, PositionComponent { 1.0f, 2.0f });
    ecs.AddComponent(entity2, VelocityComponent { 1.0f, 0.0f });

    MoveSystem move1(entity1);
    MoveSystem move2(entity2);

    ecs.AddSystem(&move1);
    ecs.AddSystem(&move2);

    while (true)
    {
        ecs.Update();
    }

    return 0;
}
