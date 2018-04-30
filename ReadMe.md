## 项目构架

c++

采用MVVM模式构建

图形界面使用Qt

## 关于AI部分说明

人工智能算法主要写在AI类（AI.cpp和AI.h）中

当人走一步棋后，会调用AI中getMove函数，该函数会将AI类里的player设置为AI对应的player号，再调用initializeInfo函数更新AI类中的int cb成员，将其改为新的棋盘状态。（-1: 空 0和1分别表示白和黑，哪个是哪个来着emm，反正之前设的player是0就表示AI要走0这些棋，1也一样）

这个函数返回一个含有4个int(x,y,z,w)的tuple，表示从(x, y)的棋移到(z, w)。

中间的switch(difficulty)是假装设置了三种难度的AI，但最后可能只能实现一种，可以删除剩下两个。

目前AI类其他函数。GenerateMove，generateMoveList，只是为了实现一个AI随机走棋，用于测试，最后需删除。

- 所以对AI的修改主要是最后getMove函数返回给我AI计算的结果就行。

## 图形界面和其他

- 游戏吃棋没有实现
- 游戏Game over判断没有实现
- 先后手选择写了一点待验证
- 需要代码整理