
#pragma once

typedef struct SnakeBody {
	char *loc;						// ��¼����Ϣ
	struct SnakeBody * next;			// ��һ��λ��
}Snake;

typedef struct FoodData {
	int X;
	int Y;
	char *loc;
}Food;

struct GameData {
	// ̰���ߵ�����
	Snake * pHead;
	Snake * pNewHead;
	// ʳ������
	Food food;
	// λ�úͷ�������
	int headX;
	int headY;
	char dir;
	char backdir;
	char newdir;
	// ��Ϸ������־
	unsigned int gameContinue;
};