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
pSnake *head;							// ��ͷָ��
struct Food food;						// ����

// ��������
pSnake *InitSnake();
void PrintScreen();
void GenFood();
void SnakeWalk(pSnake *);


void main(void) {

	// ����
	char dir = RIGHT;					// ̰���ߵ��˶�����
	char backdir = LEFT;				// ��Ӧ�ķ�����
	int X = 0;							// ��ǰ��ͷ������
	int Y = INITLEN - 1;				// ��ǰ��ͷ������
	boolean gameContinue = TRUE;		// �ж���Ϸ����

	// ��ʱ����
	char newdir;						// �µķ���
	pSnake *pendingHead;				// �µ���ͷָ��
	int pendingX;						// �µ�����
	int pendingY;

	// ��ʼ����Ļ
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++) {
			screen[i][j] = BLANK;
		}
	}

	// ��ʼ��̰����
	head = InitSnake();

	GenFood();
	
	PrintScreen();

	while (gameContinue) {
		while (TRUE) {
			newdir = getche();
			if (newdir == backdir) {
				// ���˲���
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

		// �ж���ͷλ���Ƿ������Լ�
		pSnake *temp = head;
		while (temp != NULL) {
			if (temp->loc == pendingHead->loc) {
				gameContinue = FALSE;
				break;
			}
			temp = temp->next;
		}

		// �����Ϸ��������ˢ��̰���ߺͻ���
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

	// ��ʱ(ms)
	// Sleep(1000);

	// ����
	// system("cls");
}



/*----------------------------
	���ƣ�InitSnake
	��������
	���أ�̰���ߵ�ͷ��ָ��
	���ܣ���ʼ��̰���ߵ�����
-----------------------------*/
pSnake *InitSnake() {
	pSnake *head = NULL;
	pSnake *temp = NULL;
	// β��
	for (int i = 0; i < INITLEN; i++) {
		temp = head;
		head = (pSnake*)malloc(1);
		head->loc = &screen[0][i];
		head->next = temp;
	}
	return head;
}



/*----------------------------
	���ƣ�PrintScreen
	��������
	���أ���
	���ܣ���̰��������Ļ�д�ӡ����
-----------------------------*/
void PrintScreen() {

	// ��̰������Ϣ�������Ļ
	pSnake *temp = head;
	while (temp != NULL) {
		*(temp->loc) = SNAKE;
		temp = temp->next;
	}

	// ��ʳ����Ϣ����Ļ
	*(food.loc) = FOOD;

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
	���ܣ���������
-----------------------------*/
void GenFood() {
	food.X = rand() % LEN;
	food.Y = rand() % LEN;
	food.loc = &screen[food.X][food.Y];
}


/*----------------------------
	���ƣ�SnakeWalk
	�������µ���ͷָ��
	���أ���
	���ܣ�̰�����������
-----------------------------*/
void SnakeWalk(pSnake *newHead) {
	newHead->next = head;
	head= newHead;
	// ����ߵ�ʳ���λ��
	// Ҫ�����µ�ʳ��
	// ����Ҫ��β��ɾ��
	if (head->loc == food.loc) {
		GenFood();
	}
	else {
		pSnake *temp = head;
		while (temp->next != NULL) {
			// ���tempû����һ��,˵��Ϊ�ߵ�β��
			// ��β�͵�ͼ�����
			// �ͷ�β�͵��ڴ�
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