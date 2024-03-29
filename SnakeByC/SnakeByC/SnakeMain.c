#include <stdio.h>
#include "Snake.h"
#include <windows.h>
#include <stdlib.h>
#include<conio.h>

// 函数定义
void InitScreen();
void SnakeGame();

void InitSnakeGame();
void NextHead();
void PrintScreen();
void SnakeWalk();
void GenFood();

// 全局变量定义
char screen[LEN][LEN];							// 屏幕数据
struct SnakeGameData snakeGameData;				// 游戏数据

void main(void) {

	SnakeGame();

}

/*----------------------------
	名称：SnakeGame
	参数：无
	返回：无
	功能：贪吃蛇游戏入口
-----------------------------*/
void SnakeGame() {

	// 初始化贪吃蛇
	InitSnakeGame();

	// 初始化屏幕
	InitScreen();

	// 游戏正式开始
	while (snakeGameData.gameContinue) {

		// 刷新显示
		system("cls");
		PrintScreen();

		// 延时300ms
		Sleep(300);

		if (_kbhit()) {
			snakeGameData.newdir = _getch();
		}
		else {
			snakeGameData.newdir = snakeGameData.dir;
		}

		// 计算下一步的位置
		NextHead();

		// 判断游戏继续
		if (snakeGameData.pNewHead == NULL) {
			// 没有下一个蛇头
			// 说明蛇头超过边界
			// 游戏结束
			snakeGameData.gameContinue = 0;
		}
		else {
			// 如果碰到了自己
			// 游戏结束
			Snake *temp = snakeGameData.pHead;
			while (temp != NULL) {
				if (temp->location == snakeGameData.pNewHead->location) {
					snakeGameData.gameContinue = 0;
					break;
				}
				temp = temp->next;
			}
		}

		// 如果游戏继续，则刷新贪吃蛇和画面
		if (snakeGameData.gameContinue) {
			// 更新蛇头和食物位置
			SnakeWalk();
		}
	}
}

/*----------------------------
	名称：InitSnakeGame
	参数：无
	返回：无
	功能：初始化贪吃蛇游戏数据
-----------------------------*/
void InitSnakeGame() {
	// 初始化所有数据
	int index;
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++) {
			index = i * LEN + j;
			snakeGameData.locations[index].X = i;
			snakeGameData.locations[index].Y = j;
		}
	}

	// 初始化蛇头
	Snake *pHead = NULL;
	Snake *temp = NULL;
	// 尾巴
	for (int j = 0; j < INITLEN; j++) {
		temp = pHead;
		pHead = (Snake*)malloc(1);
		pHead->location = &(snakeGameData.locations[0*LEN+j]);
		pHead->next = temp;
	}
	snakeGameData.pHead = pHead;
	snakeGameData.pNewHead = NULL;

	// 产生第一个食物
	GenFood();

	// 初始化游戏数据
	snakeGameData.dir = RIGHT;
	snakeGameData.backdir = LEFT;
	snakeGameData.newdir = snakeGameData.dir;

	// 设置游戏开始标志
	snakeGameData.gameContinue = 1;
}

/*----------------------------
	名称：InitScreen
	参数：无
	返回：无
	功能：初始化屏幕显示
-----------------------------*/
void InitScreen(){
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++) {
			screen[i][j] = BLANK;
		}
	}
}

/*----------------------------
	名称：NextHead
	参数：无
	返回：无
	功能：判断下一次蛇头的运动方向
-----------------------------*/
void NextHead() {

	int pendingX;					// 新的坐标
	int pendingY;

	if ((snakeGameData.newdir != UP) && 
		(snakeGameData.newdir != DOWN) && 
		(snakeGameData.newdir != LEFT) && 
		(snakeGameData.newdir != RIGHT)) {
		// 如果不在这几条指令内
		snakeGameData.newdir = snakeGameData.dir;
	}

	if (snakeGameData.newdir == snakeGameData.backdir) {
		// 后退当作前进处理
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
	名称：PrintScreen
	参数：无
	返回：无
	功能：将贪吃蛇在屏幕中打印出来
-----------------------------*/
void PrintScreen() {

	int x, y;
	InitScreen();

	// 将贪吃蛇信息输出给屏幕
	Snake *temp = snakeGameData.pHead;
	while (temp != NULL) {
		x = temp->location->X;
		y = temp->location->Y;
		screen[x][y] = SNAKE;
		temp = temp->next;
	}

	// 将食物信息给屏幕
	x = snakeGameData.food->X;
	y = snakeGameData.food->Y;
	screen[x][y] = FOOD;

	// 打印屏幕
	for (int i = 0; i < LEN; i++) {
		printf("| ");
		for (int j = 0; j < LEN; j++) {
			printf("%c ", screen[i][j]);
		}
		printf("|\n");
	}
}

/*----------------------------
	名称：GenFood
	参数：无
	返回：无
	功能：产生食物
-----------------------------*/
void GenFood() {
	int x, y;
	x = rand() % LEN;
	y = rand() % LEN;
	snakeGameData.food = &snakeGameData.locations[x*LEN + y];
}

/*----------------------------
	名称：SnakeWalk
	参数：无
	返回：无
	功能：贪吃蛇身体更新
-----------------------------*/
void SnakeWalk() {

	// 蛇头更新
	snakeGameData.pNewHead->next = snakeGameData.pHead;
	snakeGameData.pHead = snakeGameData.pNewHead;

	// 如果走到食物的位置，要产生新的食物
	// 否则要把尾巴删掉
	if (snakeGameData.pHead->location == snakeGameData.food) {
		GenFood();
	}
	else {
		Snake *temp = snakeGameData.pHead;
		while (temp->next != NULL) {
			// 如果temp没有下一个,说明为蛇的尾巴
			// 把尾巴的图形清空，释放尾巴的指针
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