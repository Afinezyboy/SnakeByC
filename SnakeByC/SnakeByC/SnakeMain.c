#include <stdio.h>
#include "Snake.h"
#include <windows.h>
#include <stdlib.h>

// ������Ļ��С
#define LEN		20

// ����հ��ַ�
#define BLANK	' '
// �����ߵ�ͼ��
#define SNAKE	'o'
// ����ʳ���ͼ��
#define FOOD	'@'

// �����ߵĳ�ʼ��С
#define INITLEN	5

// �����������ҵĲ�����
#define UP		'w'
#define DOWN	's'
#define LEFT	'a'
#define RIGHT	'd'


// ��̬����
char screen[LEN][LEN];					// ��Ļ

// ��������
void InitScreen();
void SnakeGame();

void InitSnake(struct GameData *);
void NextHead(struct GameData*);
void PrintScreen(struct GameData*);
void SnakeWalk(struct GameData*);

Food GenFood();



void main(void) {

	SnakeGame();
	
}

/*----------------------------
	���ƣ�SnakeGame()
	��������
	���أ���
	���ܣ�̰������Ϸ���
-----------------------------*/
void SnakeGame() {
	// ��Ϸ����
	struct GameData gameData;				// ��Ϸ����

	// ��ʼ��̰����
	InitSnake(&gameData);

	// ��ʼ����Ļ
	InitScreen();

	// ��ӡ��Ļ
	PrintScreen(&gameData);

	// ��Ϸ��ʽ��ʼ
	while (gameData.gameContinue) {

		// ���·���
		gameData.newdir = getche();

		// ������һ����λ��
		NextHead(&gameData);

		// �ж���Ϸ����
		if (gameData.pNewHead == NULL) {
			// û����һ����ͷ
			// ˵����ͷ�����߽�
			// ��Ϸ����
			gameData.gameContinue = 0;
		}
		else {
			// ����������Լ�
			// ��Ϸ����
			Snake *temp = gameData.pHead;
			while (temp != NULL) {
				if (temp->loc == gameData.pNewHead->loc) {
					gameData.gameContinue = 0;
					break;
				}
				temp = temp->next;
			}
		}

		// �����Ϸ��������ˢ��̰���ߺͻ���
		if (gameData.gameContinue) {
			// ������ͷ��ʳ��λ��
			SnakeWalk(&gameData);
		}
		else {
			break;
		}
		// ˢ����ʾ
		system("cls");
		PrintScreen(&gameData);
	}
}

/*----------------------------
	���ƣ�InitSnake
	������GameDataָ��
	���أ���
	���ܣ���ʼ��̰������Ϸ����
-----------------------------*/
void InitSnake(struct GameData * pGameData) {
	// ��ʼ����ͷ
	Snake *pHead = NULL;
	Snake *temp = NULL;
	// β��
	for (int i = 0; i < INITLEN; i++) {
		temp = pHead;
		pHead = (Snake*)malloc(1);
		pHead->loc = &screen[0][i];
		pHead->next = temp;
	}
	pGameData->pHead = pHead;

	// ������һ��ʳ��
	pGameData->food = GenFood();

	// ��ʼ����Ϸ����
	pGameData->headX = 0;
	pGameData->headY = INITLEN - 1;
	pGameData->dir = RIGHT;
	pGameData->backdir = LEFT;
	pGameData->gameContinue = 1;
}

/*----------------------------
	���ƣ�InitScreen
	��������
	���أ���
	���ܣ���ʼ����Ļ��ʾ
-----------------------------*/
void InitScreen(){
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++) {
			screen[i][j] = BLANK;
		}
	}
}

/*----------------------------
	���ƣ�NextHead
	������GameDataָ��
	���أ���
	���ܣ��ж���һ����ͷ���˶�����
-----------------------------*/
void NextHead(struct GameData* pGameData) {

	int pendingX;					// �µ�����
	int pendingY;

	if ((pGameData->newdir != UP) && 
		(pGameData->newdir != DOWN) && 
		(pGameData->newdir != LEFT) && 
		(pGameData->newdir != RIGHT)) {
		// ��������⼸��ָ����
		pGameData->newdir = pGameData->dir;
	}

	if (pGameData->newdir == pGameData->backdir) {
		// ���˵���ǰ������
		pGameData->newdir = pGameData->dir;
	}
	switch (pGameData->newdir) {
	case UP:
		pGameData->dir = UP;
		pGameData->backdir = DOWN;
		pendingX = pGameData->headX - 1;
		pendingY = pGameData->headY;
		break;
	case DOWN:
		pGameData->dir = DOWN;
		pGameData->backdir = UP;
		pendingX = pGameData->headX + 1;
		pendingY = pGameData->headY;
		break;
	case LEFT:
		pGameData->dir = LEFT;
		pGameData->backdir = RIGHT;
		pendingX = pGameData->headX;
		pendingY = pGameData->headY - 1;
		break;
	case RIGHT:
		pGameData->dir = RIGHT;
		pGameData->backdir = LEFT;
		pendingX = pGameData->headX;
		pendingY = pGameData->headY + 1;
		break;
	}
	if ((pendingX < 0) || (pendingX >= LEN) || (pendingY < 0) || (pendingY >= LEN)) {
		pGameData->pNewHead = NULL;
	}
	else {
		pGameData->pNewHead = (Snake *)malloc(1);
		pGameData->pNewHead->loc = &screen[pendingX][pendingY];
		pGameData->headX = pendingX;
		pGameData->headY = pendingY;
	}
}



/*----------------------------
	���ƣ�PrintScreen
	������GameDataָ��
	���أ���
	���ܣ���̰��������Ļ�д�ӡ����
-----------------------------*/
void PrintScreen(struct GameData * pGameData) {

	// ��̰������Ϣ�������Ļ
	Snake *temp = pGameData->pHead;
	while (temp != NULL) {
		*(temp->loc) = SNAKE;
		temp = temp->next;
	}

	// ��ʳ����Ϣ����Ļ
	*(pGameData->food.loc) = FOOD;

	// ��ӡ��Ļ
	for (int i = 0; i < LEN; i++) {
		printf("| ");
		for (int j = 0; j < LEN; j++) {
			printf("%c ", screen[i][j]);
		}
		printf("|\n");
	}
}

/*----------------------------
	���ƣ�GenFood
	��������
	���أ�ʳ��struct
	���ܣ�����ʳ��
-----------------------------*/
Food GenFood() {
	Food food;
	food.X = rand() % LEN;
	food.Y = rand() % LEN;
	food.loc = &screen[food.X][food.Y];
	return food;
}


/*----------------------------
	���ƣ�SnakeWalk
	������GameDataָ��
	���أ���
	���ܣ�̰�����������
-----------------------------*/
void SnakeWalk(struct GameData * pGameData) {

	// ��ͷ����
	pGameData->pNewHead->next = pGameData->pHead;
	pGameData->pHead = pGameData->pNewHead;

	// ����ߵ�ʳ���λ�ã�Ҫ�����µ�ʳ��
	// ����Ҫ��β��ɾ��
	if (pGameData->pHead->loc == pGameData->food.loc) {
		pGameData->food = GenFood();
	}
	else {
		Snake *temp = pGameData->pHead;
		while (temp->next != NULL) {
			// ���tempû����һ��,˵��Ϊ�ߵ�β��
			// ��β�͵�ͼ����գ��ͷ�β�͵�ָ��
			if (temp->next->next == NULL) {
				*(temp->next->loc) = BLANK;
				temp->next = NULL;
			}
			else {
				temp = temp->next;
			}
		}
	}
}