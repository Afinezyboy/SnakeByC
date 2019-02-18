#include <stdio.h>
#include "Snake.h"
#include <windows.h>
#include <stdlib.h>


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

	// ��ʼ��̰����
	InitSnake();

	// ��ʼ����Ļ
	InitScreen();

	// ��ӡ��Ļ
	PrintScreen();

	// ��Ϸ��ʽ��ʼ
	while (snakeGameData.gameContinue) {

		// ���·���
		snakeGameData.newdir = getche();

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
				if (temp->loc == snakeGameData.pNewHead->loc) {
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
		else {
			break;
		}
		// ˢ����ʾ
		system("cls");
		PrintScreen();
	}
}

/*----------------------------
	���ƣ�InitSnake
	��������
	���أ���
	���ܣ���ʼ��̰������Ϸ����
-----------------------------*/
void InitSnake() {
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
	snakeGameData.pHead = pHead;
	snakeGameData.pNewHead = NULL;

	// ������һ��ʳ��
	GenFood();

	// ��ʼ����Ϸ����
	snakeGameData.headX = 0;
	snakeGameData.headY = INITLEN - 1;
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
		pendingX = snakeGameData.headX - 1;
		pendingY = snakeGameData.headY;
		break;
	case DOWN:
		snakeGameData.dir = DOWN;
		snakeGameData.backdir = UP;
		pendingX = snakeGameData.headX + 1;
		pendingY = snakeGameData.headY;
		break;
	case LEFT:
		snakeGameData.dir = LEFT;
		snakeGameData.backdir = RIGHT;
		pendingX = snakeGameData.headX;
		pendingY = snakeGameData.headY - 1;
		break;
	case RIGHT:
		snakeGameData.dir = RIGHT;
		snakeGameData.backdir = LEFT;
		pendingX = snakeGameData.headX;
		pendingY = snakeGameData.headY + 1;
		break;
	}
	if ((pendingX < 0) || (pendingX >= LEN) || (pendingY < 0) || (pendingY >= LEN)) {
		snakeGameData.pNewHead = NULL;
	}
	else {
		snakeGameData.pNewHead = (Snake *)malloc(1);
		snakeGameData.pNewHead->loc = &screen[pendingX][pendingY];
		snakeGameData.headX = pendingX;
		snakeGameData.headY = pendingY;
	}
}

/*----------------------------
	���ƣ�PrintScreen
	��������
	���أ���
	���ܣ���̰��������Ļ�д�ӡ����
-----------------------------*/
void PrintScreen() {

	// ��̰������Ϣ�������Ļ
	Snake *temp = snakeGameData.pHead;
	while (temp != NULL) {
		*(temp->loc) = SNAKE;
		temp = temp->next;
	}

	// ��ʳ����Ϣ����Ļ
	*(snakeGameData.food.loc) = FOOD;

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
void GenFood() {
	snakeGameData.food.X = rand() % LEN;
	snakeGameData.food.Y = rand() % LEN;
	snakeGameData.food.loc = &screen[snakeGameData.food.X][snakeGameData.food.Y];
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
	if (snakeGameData.pHead->loc == snakeGameData.food.loc) {
		GenFood();
	}
	else {
		Snake *temp = snakeGameData.pHead;
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