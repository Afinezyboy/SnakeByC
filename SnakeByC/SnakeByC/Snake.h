
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

// 函数定义
void InitScreen();
void SnakeGame();

void InitSnake();
void NextHead();
void PrintScreen();
void SnakeWalk();
void GenFood();

// 全局变量定义
char screen[LEN][LEN];

// 定义蛇类
typedef struct SnakeBody {
	char *loc;						// 所在位置
	struct SnakeBody * next;		// 下一个身体位置
}Snake;

// 定义食物类
typedef struct FoodData {
	int X;							// XY坐标
	int Y;
	char *loc;
}Food;

// 游戏数据类
struct SnakeGameData {

	Snake * pHead;					// 蛇头指针		
	Snake * pNewHead;				// 新的蛇头指针
	Food food;						// 食物数据

	int headX;						// 蛇头XY坐标
	int headY;
	char dir;						// 蛇头方向
	char backdir;
	char newdir;

	unsigned int gameContinue;		// 游戏继续标志

}snakeGameData;				

