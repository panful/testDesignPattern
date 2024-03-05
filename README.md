# 一、设计模式
## 01_singleton 单例模式
## 02_decorator 装饰器模式
是一种结构型设计模式，允许向一个现有的类添加新的功能，且**不影响其结构**
### 场景
- 咖啡、牛奶咖啡、茶咖啡、牛奶和茶咖啡
- 人物、穿棉袄的人、穿短袖的人、穿短袖和棉袄的人
## 03_builder 生成器模式
是一种创建型设计模式，能够分步骤创建复杂对象，需要创建一个有很多配置选项的对象时非常有用

C++构造函数委托
## 04_adapter 适配器模式
### 不同继承方式的场景适用性：
多重继承方式： 适用于适配器与被适配者之间关系紧密，而且不会引起继承二义性或者菱形继承问题的情况。
单一继承方式： 适用于需要更大灵活性、希望避免二义性问题，并且可以接受额外指针成员的情况。
### 选择将转换方法委托给另一个类的方式，通常基于以下情况：
委托类可能包含更复杂的逻辑，需要被重用或者需要分离出来进行单元测试。
委托类可能是一个已经存在的类，而你希望使用适配器模式将其接口适配成你的目标接口。
委托类可能会有多个不同的方法，而你只需要其中一个方法，因此通过委托可以选择性地将某个方法包装成适配器。
## 05_state 状态模式
是一种行为设计模式，主要考虑对象在**不同的状态**下**有不同的行为**
### 场景
- 游戏角色状态：正常、受伤、死亡，正常时可以受伤死亡；受伤时可以正常死亡；死亡时不能受伤不能正常
- 电梯状态：打开、关闭、运行、停止，打开时可以关闭停止，不能运行或再打开；关闭时可以运行停止，不能关闭或再关闭
## 06_composite 组合模式
是一种结构型设计模式，可以使用它将对象组合成**树状结构**
### 场景
- 文件夹
- 箱子可以装小的箱子，箱子也可以装物品
- 复杂订单可以包含多个子订单，子订单可以包含许多物品
## 07_strategy [策略模式](https://www.cnblogs.com/mmmmmmmmm/p/15093268.html)
是一种行为设计模式，每种策略都是一个类，且每个类都实现了同一个接口，这些策略可以由客户端随意替换
## 08_product 工厂模式
[工厂模式的区别](https://www.cnblogs.com/mmmmmmmmm/p/15474093.html)
### 简单工厂
是一种创建型设计模式，包含一个使用大量条件语句的构建函数，可根据函数的参数来选择对何种产品进行初始化并返回
### 工厂方法
是一种创建型设计模式，其在父类中提供一个创建对象的虚函数，允许子类决定创建产品的类型
简单理解就是有很多个工厂类（这个类继承自同一个父类），这些类都可以创建一个产品（这些产品继承自同一个父类）
比如有很多工厂：工厂A、工厂B、工厂C，工厂A生产鼠标、工厂B生产键盘、工厂C生产显示器，这些产品都是电脑的外设
### 抽象工厂
是一种创建型设计模式，它能创建一系列相关或相互依赖的对象。如果产品只有一个类别（鼠标或键盘，但是可以有不同的鼠标型号，或键盘型号），那就是工厂方法模式。
比如：工厂 + 产品类别
- Windows工厂 + Mouse产品
- Windows工厂 + Keyboard产品
- Linux工厂 + Mouse产品
- Linux工厂 + Keyboard产品

再比如：运输工具 + 引擎 + 控制器
- 汽车 + 内燃机 + 方向盘
- 飞机 + 喷气式发动机 + 操纵杆
## 09_observer [观察者模式](https://www.cnblogs.com/mmmmmmmmm/p/14838575.html)
又称发布订阅模式，是一种行为设计模式，允许定义一种订阅机制，可在对象事件发生时通知多个“观察”该对象的其他对象
## 10_facade 外观模式
是一种结构型设计模式，能为程序库、框架或其他复杂类提供一个简单的接口。外观类通常可以转换为单例模式，因为大部分情况下一个外观对象就足够了。
**注意**：避免外观类过于臃肿
## 11_command 命令模式
是一种数据驱动的行为设计模式。最大的优点就是去耦合，更方便的去实现业务，缺点就是类特别多，需要实现的类很多，管理上面不太方便。
## 12_proxy 代理模式
是一种结构型设计模式，让你能提供真实服务对象的替代品给客户端使用，代理接收客户端的请求并进行一些处理（访问控制和缓存等），然后再将请求传递给服务对象
## 13_templateMethod 模板方法模式
模板方法是一种行为设计模式，它在基类种定义了一个算法的框架，允许子类在不修改结构的情况下重写算法的特定步骤。
模板方法基于继承机制：它允许你通过扩展子类的部分内容来改变部分算法。策略模式基于组合机制：你可以通过对相应行为提供不同的策略来改变对象的部分行为。模板方法在类层次上运作，因此它是**静态**的。策略在对象层次上运作，因此允许在**运行时**切换行为。
## 14_bridge 桥接模式
是一种结构型设计模式，可将一个大类或一系列相关的类拆分为**抽象**和**实现**两个独立的层次结构，从而能在开发时分别使用。
和抽象工厂模式、组合模式在某些适合比较相似。桥接模式比较适合对一个模块可以多个维度拆分的情况，比如能与多个数据库服务器交互（注意和策略模式区别），图形（三角形、圆形、四边形）和颜色（红、绿、蓝）组合
## 15_flyweight 享元模式
是一种结构型设计模式，它摒弃了在每个对象中保存所有数据的方式，通过共享多个对象所共有的相同状态，让你能够在有限的内存容量中载入更多对象。
# 二、软件架构
## 01_ecs
[ECS架构开发思路整理](https://www.jianshu.com/p/5f6cd0866d86)

实体（Entity）：仅仅是一个标识
组件（Component）：仅有数据
系统（System）：仅有函数

ECS的核心需要以下几个部分
- 实体管理器，用于存储**实体**数组并进行添加删除以及赋值操作。
- 组件管理器，管理不同的组件类型，且不同组件类型内部通过id将具体**组件**与**实体**相连。
- 系统管理器，用于管理所有**系统**，按序循环执行其心跳。

比如一个游戏角色实体可以有：位置、速度等组件，系统可以有：移动、旋转等系统
## 02_mvp
[mvc mvp mtv](https://www.cnblogs.com/mmmmmmmmm/p/15437210.html)
