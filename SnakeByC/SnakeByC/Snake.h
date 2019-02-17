
#pragma once

typedef struct snakeBody {
	char *loc;						// 记录的信息
	struct snakeBody *next;			// 下一个位置
}pSnake;

struct Food {
	int X;
	int Y;
	char *loc;
};