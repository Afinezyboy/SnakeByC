
#pragma once

typedef struct snakeBody {
	char *loc;						// ��¼����Ϣ
	struct snakeBody *next;			// ��һ��λ��
}pSnake;

struct Food {
	int X;
	int Y;
	char *loc;
};