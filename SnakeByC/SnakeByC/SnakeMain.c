#include <stdio.h>
#include "Snake.h"
#include <windows.h>
#include <stdlib.h>
#include<conio.h>

// ��������
void InitScreen();
void SnakeGame();

void InitSnakeGame();
void NextHead();
void PrintScreen();
void SnakeWalk();
void GenFood();

// ȫ�ֱ�������
char screen[LEN][LEN];							// ��Ļ����
struct SnakeGameData snakeGameData;				// ��Ϸ����

void main(void) {

	SnakeGame();

}

/*----------------------------
	���ƣ�SnakeGame
	��������
	���أ���
	���ܣ�̰������Ϸ���
-----------------------------*/
void SnakeGame() {

	// ��ʼ��̰����
	InitSnakeGame();

	// ��ʼ����Ļ
	InitScreen();

	// ��Ϸ��ʽ��ʼ
	while (snakeGameData.gameContinue) {

		// ˢ����ʾ
		system("cls");
		PrintScreen();

		// ��ʱ300ms
		Sleep(300);

		if (_kbhit()) {
			snakeGameData.newdir = _getch();
		}
		else {
			snakeGameData.newdir = snakeGameData.dir;
		}

		// ������һ����λ��
		NextHead();

		// �ж���Ϸ����
		if (snakeGameData.pNewHead == NULL) {
			// û����һ����ͷ
			// ˵����ͷ�����߽�
			// ��Ϸ����
			snakeGameData.gameContinue = 0;
		}
		else {
			// ����������Լ�
			// ��Ϸ����
			Snake *temp = snakeGameData.pHead;
			while (temp != NULL) {
				if (temp->location == snakeGameData.pNewHead->location) {
					snakeGameData.gameContinue = 0;
					break;
				}
				temp = temp->next;
			}
		}

		// �����Ϸ��������ˢ��̰���ߺͻ���
		if (snakeGameData.gameContinue) {
			// ������ͷ��ʳ��λ��
			SnakeWalk();
		}
	}
}

/*----------------------------
	���ƣ�InitSnakeGame
	��������
	���أ���
	���ܣ���ʼ��̰������Ϸ����
-----------------------------*/
void InitSnakeGame() {
	// ��ʼ����������
	int index;
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++) {
			index = i * LEN + j;
			snakeGameData.locations[index].X = i;
			snakeGameData.locations[index].Y = j;
		}
	}

	// ��ʼ����ͷ
	Snake *pHead = NULL;
	Snake *temp = NULL;
	// β��
	for (int j = 0; j < INITLEN; j++) {
		temp = pHead;
		pHead = (Snake*)malloc(1);
		pHead->location = &(snakeGameData.locations[0*LEN+j]);
		pHead->next = temp;
	}
	snakeGameData.pHead = pHead;
	snakeGameData.pNewHead = NULL;

	// ������һ��ʳ��
	GenFood();

	// ��ʼ����Ϸ����
	snakeGameData.dir = RIGHT;
	snakeGameData.backdir = LEFT;
	snakeGameData.newdir = snakeGameData.dir;

	// ������Ϸ��ʼ��־
	snakeGameData.gameContinue = 1;
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
	��������
	���أ���
	���ܣ��ж���һ����ͷ���˶�����
-----------------------------*/
void NextHead() {

	int pendingX;					// �µ�����
	int pendingY;

	if ((snakeGameData.newdir != UP) && 
		(snakeGameData.newdir != DOWN) && 
		(snakeGameData.newdir != LEFT) && 
		(snakeGameData.newdir != RIGHT)) {
		// ��������⼸��ָ����
		snakeGameData.newdir = snakeGameData.dir;
	}

	if (snakeGameData.newdir == snakeGameData.backdir) {
		// ���˵���ǰ������
		snakeGameData.newdir = snakeGameData.dir;
	}
	switch (snakeGameData.newdir) {
	case UP:
		snakeGameData.dir = UP;
		snakeGameData.backdir = DOWN;
		pendingX = snakeGameData.pHead->location->X - 1;
		pendingY = snakeGameData.pHead->location->Y;
		break;
	case DOWN:
		snakeGameData.dir = DOWN;
		snakeGameData.backdir = UP;
		pendingX = snakeGameData.pHead->location->X + 1;
		pendingY = snakeGameData.pHead->location->Y;
		break;
	case LEFT:
		snakeGameData.dir = LEFT;
		snakeGameData.backdir = RIGHT;
		pendingX = snakeGameData.pHead->location->X;
		pendingY = snakeGameData.pHead->location->Y - 1;
		break;
	case RIGHT:
		snakeGameData.dir = RIGHT;
		snakeGameData.backdir = LEFT;
		pendingX = snakeGameData.pHead->location->X;
		pendingY = snakeGameData.pHead->location->Y + 1;
		break;
	}
	if ((pendingX < 0) || (pendingX >= LEN) || (pendingY < 0) || (pendingY >= LEN)) {
		snakeGameData.pNewHead = NULL;
	}
	else {
		snakeGameData.pNewHead = (Snake *)malloc(1);
		snakeGameData.pNewHead->location = &snakeGameData.locations[pendingX*LEN + pendingY];
	}
}

/*----------------------------
	���ƣ�PrintScreen
	��������
	���أ���
	���ܣ���̰��������Ļ�д�ӡ����
-----------------------------*/
void PrintScreen() {

	int x, y;
	InitScreen();

	// ��̰������Ϣ�������Ļ
	Snake *temp = snakeGameData.pHead;
	while (temp != NULL) {
		x = temp->location->X;
		y = temp->location->Y;
		screen[x][y] = SNAKE;
		temp = temp->next;
	}

	// ��ʳ����Ϣ����Ļ
	x = snakeGameData.food->X;
	y = snakeGameData.food->Y;
	screen[x][y] = FOOD;

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
	���أ���
	���ܣ�����ʳ��
-----------------------------*/
void GenFood() {
	int x, y;
	x = rand() % LEN;
	y = rand() % LEN;
	snakeGameData.food = &snakeGameData.locations[x*LEN + y];
}

/*----------------------------
	���ƣ�SnakeWalk
	��������
	���أ���
	���ܣ�̰�����������
-----------------------------*/
void SnakeWalk() {

	// ��ͷ����
	snakeGameData.pNewHead->next = snakeGameData.pHead;
	snakeGameData.pHead = snakeGameData.pNewHead;

	// ����ߵ�ʳ���λ�ã�Ҫ�����µ�ʳ��
	// ����Ҫ��β��ɾ��
	if (snakeGameData.pHead->location == snakeGameData.food) {
		GenFood();
	}
	else {
		Snake *temp = snakeGameData.pHead;
		while (temp->next != NULL) {
			// ���tempû����һ��,˵��Ϊ�ߵ�β��
			// ��β�͵�ͼ����գ��ͷ�β�͵�ָ��
			if (temp->next->next == NULL) {
				// *(temp->next->loc) = BLANK;
				temp->next = NULL;
			}
			else {
				temp = temp->next;
			}
		}
	}
}