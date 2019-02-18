
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


// ����λ����
typedef struct Location {
	int X;
	int Y;
}Location;

// ��������
typedef struct Snake {
	Location * location;			// ����λ�õ�ָ��
	struct Snake * next;			// ��һ������λ��
}Snake;

// ��Ϸ������
struct SnakeGameData {

	Location locations[LEN*LEN];	// ȫ��λ��

	Snake * pHead;					// ��ͷָ��		
	Snake * pNewHead;				// �µ���ͷָ��

	Location * food;				// ʳ��λ��ָ��

	char dir;						// ��ͷ����
	char backdir;
	char newdir;
		
	int refreshFlag;				// ��Ļˢ�±�־λ

	unsigned int gameContinue;		// ��Ϸ������־

};				

