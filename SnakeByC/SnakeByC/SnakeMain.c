#include <stdio.h>
#include "Snake.h"
#include <windows.h>
#include <stdlib.h>

// 定义屏幕大小
#define LEN		20

// 定义空白字符
#define BLANK	' '
// 定义蛇的图案
#define SNAKE	'o'
// 定义食物的图案
#define FOOD	'@'

// 定义蛇的初始大小
#define INITLEN	5

// 定义上下左右的操作键
#define UP		'w'
#define DOWN	's'
#define LEFT	'a'
#define RIGHT	'd'


// 静态变量
char screen[LEN][LEN];					// 屏幕

// 函数定义
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
	名称：SnakeGame()
	参数：无
	返回：无
	功能：贪吃蛇游戏入口
-----------------------------*/
void SnakeGame() {
	// 游戏变量
	struct GameData gameData;				// 游戏数据

	// 初始化贪吃蛇
	InitSnake(&gameData);

	// 初始化屏幕
	InitScreen();

	// 打印屏幕
	PrintScreen(&gameData);

	// 游戏正式开始
	while (gameData.gameContinue) {

		// 更新方向
		gameData.newdir = getche();

		// 计算下一步的位置
		NextHead(&gameData);

		// 判断游戏继续
		if (gameData.pNewHead == NULL) {
			// 没有下一个蛇头
			// 说明蛇头超过边界
			// 游戏结束
			gameData.gameContinue = 0;
		}
		else {
			// 如果碰到了自己
			// 游戏结束
			Snake *temp = gameData.pHead;
			while (temp != NULL) {
				if (temp->loc == gameData.pNewHead->loc) {
					gameData.gameContinue = 0;
					break;
				}
				temp = temp->next;
			}
		}

		// 如果游戏继续，则刷新贪吃蛇和画面
		if (gameData.gameContinue) {
			// 更新蛇头和食物位置
			SnakeWalk(&gameData);
		}
		else {
			break;
		}
		// 刷新显示
		system("cls");
		PrintScreen(&gameData);
	}
}

/*----------------------------
	名称：InitSnake
	参数：GameData指针
	返回：无
	功能：初始化贪吃蛇游戏数据
-----------------------------*/
void InitSnake(struct GameData * pGameData) {
	// 初始化蛇头
	Snake *pHead = NULL;
	Snake *temp = NULL;
	// 尾巴
	for (int i = 0; i < INITLEN; i++) {
		temp = pHead;
		pHead = (Snake*)malloc(1);
		pHead->loc = &screen[0][i];
		pHead->next = temp;
	}
	pGameData->pHead = pHead;

	// 产生第一个食物
	pGameData->food = GenFood();

	// 初始化游戏数据
	pGameData->headX = 0;
	pGameData->headY = INITLEN - 1;
	pGameData->dir = RIGHT;
	pGameData->backdir = LEFT;
	pGameData->gameContinue = 1;
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
	参数：GameData指针
	返回：无
	功能：判断下一次蛇头的运动方向
-----------------------------*/
void NextHead(struct GameData* pGameData) {

	int pendingX;					// 新的坐标
	int pendingY;

	if ((pGameData->newdir != UP) && 
		(pGameData->newdir != DOWN) && 
		(pGameData->newdir != LEFT) && 
		(pGameData->newdir != RIGHT)) {
		// 如果不在这几条指令内
		pGameData->newdir = pGameData->dir;
	}

	if (pGameData->newdir == pGameData->backdir) {
		// 后退当作前进处理
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
	名称：PrintScreen
	参数：GameData指针
	返回：无
	功能：将贪吃蛇在屏幕中打印出来
-----------------------------*/
void PrintScreen(struct GameData * pGameData) {

	// 将贪吃蛇信息输出给屏幕
	Snake *temp = pGameData->pHead;
	while (temp != NULL) {
		*(temp->loc) = SNAKE;
		temp = temp->next;
	}

	// 将食物信息给屏幕
	*(pGameData->food.loc) = FOOD;

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
	返回：食物struct
	功能：产生食物
-----------------------------*/
Food GenFood() {
	Food food;
	food.X = rand() % LEN;
	food.Y = rand() % LEN;
	food.loc = &screen[food.X][food.Y];
	return food;
}


/*----------------------------
	名称：SnakeWalk
	参数：GameData指针
	返回：无
	功能：贪吃蛇身体更新
-----------------------------*/
void SnakeWalk(struct GameData * pGameData) {

	// 蛇头更新
	pGameData->pNewHead->next = pGameData->pHead;
	pGameData->pHead = pGameData->pNewHead;

	// 如果走到食物的位置，要产生新的食物
	// 否则要把尾巴删掉
	if (pGameData->pHead->loc == pGameData->food.loc) {
		pGameData->food = GenFood();
	}
	else {
		Snake *temp = pGameData->pHead;
		while (temp->next != NULL) {
			// 如果temp没有下一个,说明为蛇的尾巴
			// 把尾巴的图形清空，释放尾巴的指针
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