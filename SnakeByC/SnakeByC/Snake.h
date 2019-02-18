
#pragma once

typedef struct SnakeBody {
	char *loc;						// 记录的信息
	struct SnakeBody * next;			// 下一个位置
}Snake;

typedef struct FoodData {
	int X;
	int Y;
	char *loc;
}Food;

struct GameData {
	// 贪吃蛇的数据
	Snake * pHead;
	Snake * pNewHead;
	// 食物数据
	Food food;
	// 位置和方向数据
	int headX;
	int headY;
	char dir;
	char backdir;
	char newdir;
	// 游戏继续标志
	unsigned int gameContinue;
};