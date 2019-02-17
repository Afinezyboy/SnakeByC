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
pSnake *head;							// 蛇头指针
struct Food food;						// 种子

// 函数定义
pSnake *InitSnake();
void PrintScreen();
void GenFood();
void SnakeWalk(pSnake *);


void main(void) {

	// 数据
	char dir = RIGHT;					// 贪吃蛇的运动方向
	char backdir = LEFT;				// 对应的反方向
	int X = 0;							// 当前蛇头横坐标
	int Y = INITLEN - 1;				// 当前蛇头纵坐标
	boolean gameContinue = TRUE;		// 判断游戏继续

	// 临时数据
	char newdir;						// 新的方向
	pSnake *pendingHead;				// 新的蛇头指针
	int pendingX;						// 新的坐标
	int pendingY;

	// 初始化屏幕
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++) {
			screen[i][j] = BLANK;
		}
	}

	// 初始化贪吃蛇
	head = InitSnake();

	GenFood();
	
	PrintScreen();

	while (gameContinue) {
		while (TRUE) {
			newdir = getche();
			if (newdir == backdir) {
				// 后退不算
				continue;
			}
			else if (newdir == UP) {
				dir = UP;
				backdir = DOWN;
				pendingX = X - 1;
				pendingY = Y;
				break;
			}
			else if (newdir == DOWN) {
				dir = DOWN;
				backdir = UP;
				pendingX = X + 1;
				pendingY = Y;
				break;
			}
			else if (newdir == LEFT) {
				dir = LEFT;
				backdir = RIGHT;
				pendingX = X;
				pendingY = Y - 1;
				break;
			}
			else if (newdir == RIGHT) {
				dir = RIGHT;
				backdir = LEFT;
				pendingX = X;
				pendingY = Y + 1;
				break;
			}
		}
		if ((pendingX < 0) || (pendingX >= LEN) || (pendingY < 0) || (pendingY >= LEN)) {
			gameContinue = FALSE;
		}
		pendingHead = (pSnake*)malloc(1);
		pendingHead->loc = &screen[pendingX][pendingY];

		// 判断蛇头位置是否碰到自己
		pSnake *temp = head;
		while (temp != NULL) {
			if (temp->loc == pendingHead->loc) {
				gameContinue = FALSE;
				break;
			}
			temp = temp->next;
		}

		// 如果游戏继续，则刷新贪吃蛇和画面
		if (gameContinue) {
			SnakeWalk(pendingHead);
			system("cls");
			PrintScreen();
			X = pendingX;
			Y = pendingY;
		}
	}

	// c = getche();

	// printf("%c", c);

	// 延时(ms)
	// Sleep(1000);

	// 清屏
	// system("cls");
}



/*----------------------------
	名称：InitSnake
	参数：无
	返回：贪吃蛇的头部指针
	功能：初始化贪吃蛇的身体
-----------------------------*/
pSnake *InitSnake() {
	pSnake *head = NULL;
	pSnake *temp = NULL;
	// 尾巴
	for (int i = 0; i < INITLEN; i++) {
		temp = head;
		head = (pSnake*)malloc(1);
		head->loc = &screen[0][i];
		head->next = temp;
	}
	return head;
}



/*----------------------------
	名称：PrintScreen
	参数：无
	返回：无
	功能：将贪吃蛇在屏幕中打印出来
-----------------------------*/
void PrintScreen() {

	// 将贪吃蛇信息输出给屏幕
	pSnake *temp = head;
	while (temp != NULL) {
		*(temp->loc) = SNAKE;
		temp = temp->next;
	}

	// 将食物信息给屏幕
	*(food.loc) = FOOD;

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
	功能：产生种子
-----------------------------*/
void GenFood() {
	food.X = rand() % LEN;
	food.Y = rand() % LEN;
	food.loc = &screen[food.X][food.Y];
}


/*----------------------------
	名称：SnakeWalk
	参数：新的蛇头指针
	返回：无
	功能：贪吃蛇身体更新
-----------------------------*/
void SnakeWalk(pSnake *newHead) {
	newHead->next = head;
	head= newHead;
	// 如果走到食物的位置
	// 要产生新的食物
	// 否则要把尾巴删掉
	if (head->loc == food.loc) {
		GenFood();
	}
	else {
		pSnake *temp = head;
		while (temp->next != NULL) {
			// 如果temp没有下一个,说明为蛇的尾巴
			// 把尾巴的图形清空
			// 释放尾巴的内存
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