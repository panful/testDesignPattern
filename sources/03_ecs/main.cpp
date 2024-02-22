#include <iostream>
#include <vector>
#include <unordered_map>

// 定义组件
struct PositionComponent {
    float x, y;
};

struct RenderComponent {
    std::string sprite;
};

// 定义实体
struct Entity {
    int id;
};

// 定义系统
class System {
public:
    virtual void Update() = 0;
};

class RenderSystem : public System {
public:
    RenderSystem(std::unordered_map<int, PositionComponent>& positions, std::unordered_map<int, RenderComponent>& renderables)
        : positions_(positions), renderables_(renderables) {}

    void Update() override {
        for (const auto& pair : renderables_) {
            int entityId = pair.first;
            if (positions_.find(entityId) != positions_.end()) {
                const PositionComponent& position = positions_[entityId];
                const RenderComponent& renderable = renderables_[entityId];
                std::cout << "Render " << renderable.sprite << " at (" << position.x << ", " << position.y << ")\n";
            }
        }
    }

private:
    std::unordered_map<int, PositionComponent>& positions_;
    std::unordered_map<int, RenderComponent>& renderables_;
};

// ECS管理器
class ECS {
public:
    Entity CreateEntity() {
        Entity entity{nextEntityId_++};
        entities_.push_back(entity);
        return entity;
    }

    void AddComponent(Entity entity, PositionComponent position) {
        positions_[entity.id] = position;
    }

    void AddComponent(Entity entity, RenderComponent renderable) {
        renderables_[entity.id] = renderable;
    }

    void Update() {
        for (auto& system : systems_) {
            system->Update();
        }
    }

public:
    std::vector<Entity> entities_;
    std::unordered_map<int, PositionComponent> positions_;
    std::unordered_map<int, RenderComponent> renderables_;
    std::vector<System*> systems_;
    int nextEntityId_ = 1;
};

int main() {
    ECS ecs;
    Entity entity1 = ecs.CreateEntity();
    Entity entity2 = ecs.CreateEntity();

    ecs.AddComponent(entity1, {10.0f, 20.0f});
    ecs.AddComponent(entity2, {30.0f, 40.0f});
    ecs.AddComponent(entity1, {"PlayerSprite"});
    ecs.AddComponent(entity2, {"EnemySprite"});

    RenderSystem renderSystem(ecs.positions_, ecs.renderables_);
    ecs.systems_.push_back(&renderSystem);

    while (true) {
        ecs.Update();
    }

    return 0;
}
