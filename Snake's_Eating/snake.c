//snake.c -- 贪吃蛇游戏函数定义
#define _CRT_SECURE_NO_WARNINGS
#include "snake.h"

Snake* snake = NULL;
Map* map = NULL;
Food* food = NULL;
bool isExit = false;

char mapBlock = ' ';
char snakeBlock = 'O';
char foodBlock = '*';

void createMap(int width, int high)
{
	int** temp;
	int row;
	int col;

	map = (Map*)malloc(sizeof(Map));
	if (2 > width || 2 > high)
	{
		map->high = HIGH;
		map->width = WIDTH;
		printf("地图长宽不合法，已重置为 %d * %d\n", WIDTH, HIGH);
	}
	else
	{
		map->high = high;
		map->width = width;
	}

	//创建地图
	temp = (int**)malloc(high * sizeof(int*));	//申请地图行
	for (row = 0; row < high; row++)
	{
		temp[row] = (int*)malloc(width * sizeof(int));//申请该行的地图列
		for (col = 0; col < width; col++)
		{
			temp[row][col] = 0; //地图格初始化
		}
	}
	map->map = temp;

	return;
}

void destroyMap(void)
{
	if (!map) return;
	int row;
	int** temp;

	temp = map->map;
	for (row = 0; row < map->high; row++)
	{
		free(temp[row]);
	}
	free(temp);
	free(map);
	map = NULL;
	return;
}

int isMapBlockFilled(int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->high) return 1;

	int i;
	SnakeBody* body = snake->bodys;

	//检查蛇每一节是否占据目标位置
	for (i = 0; i < snake->length; i++)
	{
		if (x == body->x && y == body->y) return 1;
		body = body->next;
	}

	return 0;
}

void showMap(void)
{
	int row, col;
	int len;
	SnakeBody* body = snake->bodys;

	//刷新地图
	for (row = 0; row < map->high; row++)
	{
		for (col = 0; col < map->width; col++)
			map->map[row][col] = mblock;
	}

	for (len = 0; len < snake->length; len++)
	{
		map->map[body->y][body->x] = sblock;
		body = body->next;
	}

	map->map[food->y][food->x] = fblock;

	//打印地图
	for (row = 0; row < map->high; row++)
	{
		for (col = 0; col < map->width; col++)
			//枚举是哪种类型，显示
			//printf("%d", map->map[row][col]);
			switch (map->map[row][col])
			{
			case mblock:
				printf("%c ", mapBlock);
				break;
			case sblock:
				printf("%c ", snakeBlock);
				break;
			case fblock:
				printf("%c ", foodBlock);
				break;
			default:
				break;
			}
		printf("|\n");
	}
	for (col = 0; col < map->width; col++)printf("--");
	printf("\n");
}

Snake* createSnake(int length)
{
	if ((map->width / 2) < length)
	{
		length = LENGTH;
		printf("蛇初始长度不合法，已重置为 %d\n", LENGTH);
	}

	int i;
	SnakeBody* body = NULL;

	//蛇体创建
	for (i = length - 1; i >= 0; i--)
	{
		SnakeBody* head = (SnakeBody*)malloc(sizeof(SnakeBody));
		head->next = body;
		head->y = map->high / 2;
		head->x = map->width / 2 - i;
		body = head;
	}

	//创建蛇
	snake = (Snake*)malloc(sizeof(Snake));
	snake->drct = right;
	snake->bodys = body;
	snake->minLength = length;
	snake->length = length;
	snake->isDead = false;

	return snake;
}

void forward(SnakeBody* nextBlock, SnakeBody* finalBody)
{
	//下一格是空地
	nextBlock->next = snake->bodys;
	snake->bodys = nextBlock;
	free(finalBody->next);
	finalBody->next = NULL;
	return;
}

void eat(SnakeBody* nextBlock)
{
	//吃到食物
	nextBlock->next = snake->bodys;
	snake->bodys = nextBlock;
	snake->length++;
	createFood();
	return;
}

void die(void)
{
	snake->isDead = true;
}

void destroySnake(void)
{
	if (!snake) return;
	int i;
	SnakeBody* temp = NULL;

	for (i = 0; i < snake->length; i++)
	{
		temp = snake->bodys;
		snake->bodys = snake->bodys->next;
		free(temp);
	}
	free(snake);
	snake = NULL;
	return;
}

void createFood(void)
{
	int x, y;

	if (!food) food = (Food*)malloc(sizeof(Food));
	while (1) {
		x = rand() % map->width;
		y = rand() % map->high;
		if (!isMapBlockFilled(x, y))
			break;
	}

	food->x = x;
	food->y = y;
	return;
}

void destroyFood(void)
{
	if (!food) return;
	free(food);
}

int initGame(void)
{
	//设置随机数种子
	srand((time_t)time(NULL));

	//初始化地图、蛇、食物
	createMap(60, 30);
	createSnake(3);
	createFood();

	return 0;
}

int resetGame(void)
{
	//重置蛇属性、重置水果位置
	int i;
	SnakeBody* body = NULL;

	for (i = 0; i < snake->length; i++)
	{
		SnakeBody* temp = snake->bodys;
		snake->bodys = snake->bodys->next;
		free(temp);
	}
	//for (i = 0; i < snake->minLength; i++)
	//{
	//	SnakeBody* head = (SnakeBody*)malloc(sizeof(SnakeBody));
	//	head->next = body;
	//	head->y = map->high / 2;
	//	head->x = map->width / 2 - i;
	//	body = head;
	//}
	for (i = snake->minLength - 1; i >= 0; i--)
	{
		SnakeBody* head = (SnakeBody*)malloc(sizeof(SnakeBody));
		head->next = body;
		head->y = map->high / 2;
		head->x = map->width / 2 - i;
		body = head;
	}
	snake->bodys = body;
	snake->drct = right;
	snake->length = snake->minLength;
	snake->isDead = false;

	createFood();

	return 0;
}

int exitGame(void)
{
	//释放地图、蛇、食物
	destroyFood();
	destroySnake();
	destroyMap();

	isExit = true;

	return 0;
}

void checkNext(void)
{
	//根据方向判断下一格是墙/身体/食物/空地
	Direction dir = snake->drct;
	SnakeBody* tempBody = snake->bodys;
	SnakeBody* finalBody = NULL;
	SnakeBody* nextBlock = (SnakeBody*)malloc(sizeof(SnakeBody));
	int i;
	switch (dir)
	{
	case up:
		nextBlock->x = tempBody->x;
		nextBlock->y = tempBody->y - 1;
		break;
	case down:
		nextBlock->x = tempBody->x;
		nextBlock->y = tempBody->y + 1;
		break;
	case left:
		nextBlock->x = tempBody->x - 1;
		nextBlock->y = tempBody->y;
		break;
	case right:
		nextBlock->x = tempBody->x + 1;
		nextBlock->y = tempBody->y;
		break;
	default:
		break;
	}
	//撞墙
	if (nextBlock->x < 0 || nextBlock->y < 0 || nextBlock->x >= map->width || nextBlock->y >= map->high)
	{
		die();
		free(nextBlock);
	}
	//吃到食物
	else if (nextBlock->x == food->x && nextBlock->y == food->y) eat(nextBlock);
	else
	{
		for (i = 0; i < snake->length-1; tempBody = tempBody->next, i++)
		{
			//下一节是该节身体
			if (tempBody->x == nextBlock->x && tempBody->y == nextBlock->y)
				break;
			//最后的2节
			if (i == snake->length - 2)
				finalBody = tempBody;
		}
		//咬到该节身体
		if (tempBody->next) {
			die();
			free(nextBlock);
		}
		//下一格为空地
		else forward(nextBlock, finalBody);
	}
	return;
}

Direction inputKey(void)
{
	int sleepTime = 0;
	Direction ch = 0;
	//清空输入缓冲区
	while (kbhit()) getch();

	while (true)
	{
		Sleep(50);
		sleepTime += 50;

		if (sleepTime >= FORWARD_TIME) break; //结束输入

		if (kbhit() && !ch)			//检测到键盘输入 且 ch未读取过输入
		{
			if ((ch = getch())==224)	//读取输入，输入的是功能键
				switch (ch = getch())
				{
				case up:	//上下左右
				case down:
				case left:
				case right:
					break;
				default:	//其他功能键
					ch = 0;
					break;
				}
			else ch = 0;	//输入的不是功能键
		}
	}

	return ch;
}

