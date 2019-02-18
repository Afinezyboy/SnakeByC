
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

// ��������
void InitScreen();
void SnakeGame();

void InitSnake();
void NextHead();
void PrintScreen();
void SnakeWalk();
void GenFood();

// ȫ�ֱ�������
char screen[LEN][LEN];

// ��������
typedef struct SnakeBody {
	char *loc;						// ����λ��
	struct SnakeBody * next;		// ��һ������λ��
}Snake;

// ����ʳ����
typedef struct FoodData {
	int X;							// XY����
	int Y;
	char *loc;
}Food;

// ��Ϸ������
struct SnakeGameData {

	Snake * pHead;					// ��ͷָ��		
	Snake * pNewHead;				// �µ���ͷָ��
	Food food;						// ʳ������

	int headX;						// ��ͷXY����
	int headY;
	char dir;						// ��ͷ����
	char backdir;
	char newdir;

	unsigned int gameContinue;		// ��Ϸ������־

}snakeGameData;				

