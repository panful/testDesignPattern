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
## 04

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
