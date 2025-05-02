# 更新记录 / Change Log

### Further Roadmap:

#### Tier 3 - 网络相关

- **多人在线模式**  
    - 支持玩家与好友或全球玩家在线对战。
    - 增加排行榜功能，展示玩家的全球排名。

- **观战模式**  
	- 允许玩家观看其他玩家的对战，学习策略或欣赏高水平比赛。

- **云存档功能**  
	- 支持云端存档，方便玩家在不同设备上继续游戏。

#### Tier 2 - 内容大改

**异形地图**
- 三角形网格、六边形网格、球面地图、双曲面地图等多种地图类型。
- （如果可能）3D地图。使用一套全新的UI和操作方式。

**关卡编辑器**  
- 允许玩家自定义地图或关卡，分享给其他玩家。

**AI改进**  
- 提升AI的智能程度，提供多种AI策略模式（如进攻型、防守型等）。

#### Tier 1 - 小改

**成就系统**  
- 增加成就解锁功能，例如完成特定任务或达到某些目标时解锁奖励。

**教程模式**  
- 为新手玩家提供详细的教程，帮助他们快速上手游戏。

**多语言支持**  
- 增加更多语言选项，吸引全球玩家。

---

### Upcoming: v2.0 pre1 (2025-6)

大幅提升游戏美术。

1. 重新设计游戏界面，提升用户体验。
  - 使用Qt设计游戏界面，提升美观性和易用性。
  - 增加音效和背景音乐，增强游戏氛围。
2. 增加游戏设置选项，允许玩家自定义游戏参数。
  - 允许玩家设置地图大小、AI难度等参数。
3. 升级游戏存档和读取功能，允许玩家保存和加载多份存档。

---

Overhaul game art.

1. Redesign game interface to enhance user experience.
  - Use Qt to design the game interface for improved aesthetics and usability.
  - Add sound effects and background music to enhance the game atmosphere.
2. Add game settings options to allow players to customize game parameters.
  - Allow players to set map size, AI difficulty, etc.
3. Upgrade game save and load functions to allow players to save and load multiple saves.

---

### Upcoming: v1.2 pre1 (2025-5)

使用现代C++技术重构游戏工程，提升性能和可维护性。
  - 使用主流工程结构；引入vcpkg和cmake构建系统，支持多平台编译。
  - 进行合理的面向对象设计。
  - 使用现代C++特性（如智能指针、范围for循环等）提升代码可读性和安全性。
  - 重构存档格式。

---

Refactor game project with modern C++ technology to improve performance and maintainability.
  - Use mainstream project structure; introduce vcpkg and cmake build system to support multi-platform compilation.
  - Conduct reasonable object-oriented design.
  - Use modern C++ features (such as smart pointers, range for loops, etc.) to improve code readability and safety.
  - Refactor save format.

---

### v1.1 (2023-01-11)

1. 取消键盘操作，改为鼠标操作，操作更加便捷。
2. 优化颜色对比度，提升辨识度。
3. 新增人机对战模式，丰富游戏玩法。
4. 增加菜单功能，操作更直观。

#### 说明：

在游戏的某一回合中部分颜色选项会被隐藏，这是基于游戏规则的设计：
1. 玩家不能选择上次倒的颜色，否则操作无效；
2. 玩家不能选择对方的颜色，否则会导致对方区域被覆盖。

---

1. Removed keyboard controls, replaced with mouse controls for easier operation.
2. Optimized color contrast for better recognition.
3. Added PVE mode to enrich gameplay.
4. Added the menu for more intuitive operation.

#### Note:

In a gameturn, certain color options will be hidden, this is a design based on the game rules:
1. Players cannot select the color of the last turn, otherwise the operation is invalid;
2. Players cannot select the opponent's color, otherwise it will cause the opponent's area to be covered.