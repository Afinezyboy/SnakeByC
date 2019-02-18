
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


// 定义位置类
typedef struct Location {
	int X;
	int Y;
}Location;

// 定义蛇类
typedef struct Snake {
	Location * location;			// 所在位置的指针
	struct Snake * next;			// 下一个身体位置
}Snake;

// 游戏数据类
struct SnakeGameData {

	Location locations[LEN*LEN];	// 全局位置

	Snake * pHead;					// 蛇头指针		
	Snake * pNewHead;				// 新的蛇头指针

	Location * food;				// 食物位置指针

	char dir;						// 蛇头方向
	char backdir;
	char newdir;
		
	int refreshFlag;				// 屏幕刷新标志位

	unsigned int gameContinue;		// 游戏继续标志

};				

